// Shooter Game. By xDedic. All Rights reserved.

#include "AMGameModeBase.h"
#include "Player/AMBaseCharacter.h"
#include "Player/AMPlayerController.h"
#include "UI/AMGameHUD.h"
#include "AIController.h"
#include "Player/AMPlayerState.h"
#include "AMUtils.h"
#include "Components/AMRespawnComponent.h"
#include "Components/AMWeaponComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAMGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

AAMGameModeBase::AAMGameModeBase()
{
	DefaultPawnClass = AAMBaseCharacter::StaticClass();
	PlayerControllerClass = AAMPlayerController::StaticClass();
	HUDClass = AAMGameHUD::StaticClass();
	PlayerStateClass = AAMPlayerState::StaticClass();
}

void AAMGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();

	SetMatchState(EAMMatchState::InProgress);
}

UClass* AAMGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AAMGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AMAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AMAIController);
	}
}

void AAMGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AAMGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AAMGameModeBase::GameTimerUpdate()
{
	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void AAMGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayers(It->Get());
	}
}

void AAMGameModeBase::ResetOnePlayers(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AAMGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AAMPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor AAMGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogAMGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void AAMGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<AAMBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<AAMPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AAMGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AAMPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AAMPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(VictimController);
}

void AAMGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AAMPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void AAMGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
	if (!RespawnAvailable) return;

	const auto RespawnComponent = AMUtils::GetAMPlayerComponent<UAMRespawnComponent>(Controller);
	if (!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);
}

void AAMGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayers(Controller);
}

void AAMGameModeBase::GameOver()
{
	// Test log
	//UE_LOG(LogAMGameModeBase, Display, TEXT("============ GAME OVER ============"));
	LogPlayerInfo();

	for (auto Pawn: TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(EAMMatchState::GameOver);
}

void AAMGameModeBase::SetMatchState(EAMMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
}

bool AAMGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		StopAllFire();
		SetMatchState(EAMMatchState::Pause);
	}
	return PauseSet;
}

bool AAMGameModeBase::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetMatchState(EAMMatchState::InProgress);
	}
	return PauseCleared;
}

void AAMGameModeBase::StopAllFire()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		const auto WeaponComponent = AMUtils::GetAMPlayerComponent<UAMWeaponComponent>(Pawn);
		if (!WeaponComponent) continue;

		WeaponComponent->StopFire();
		WeaponComponent->Zoom(false);
	}
}