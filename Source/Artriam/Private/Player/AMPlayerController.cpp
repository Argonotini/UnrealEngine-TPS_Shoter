// Shooter Game. By xDedic. All Rights reserved.

#include "Player/AMPlayerController.h"
#include "Components/AMRespawnComponent.h"
#include "AMGameModeBase.h"
#include "AMGameInstance.h"

AAMPlayerController::AAMPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UAMRespawnComponent>("RespawnComponent");
}

void AAMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<AAMGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AAMPlayerController::OnMatchStateChanged);
		}
	}
}

void AAMPlayerController::OnMatchStateChanged(EAMMatchState State)
{
	if (State == EAMMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void AAMPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void AAMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &AAMPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &AAMPlayerController::OnMuteSound);
}

void AAMPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AAMPlayerController::OnMuteSound()
{
	if (!GetWorld()) return;

	const auto AMGameInstace = GetWorld()->GetGameInstance<UAMGameInstance>();
	if (!AMGameInstace) return;

	AMGameInstace->ToggleVolume();
}