// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMGameOverWidget.h"
#include "AMGameModeBase.h"
#include "Player/AMPlayerState.h"
#include "UI/AMPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "AMUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UAMGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GetWorld())
	{
		if (const auto GameMode = Cast<AAMGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UAMGameOverWidget::OnMatchStateChanged);
		}
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &UAMGameOverWidget::OnResetLevel);
	}
}

void UAMGameOverWidget::OnMatchStateChanged(EAMMatchState State)
{
	if (State == EAMMatchState::GameOver)
	{
		UpdatePlayersStat();
	}
}

void UAMGameOverWidget::UpdatePlayersStat()
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AAMPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<UAMPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if (!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(AMUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(AMUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStatRowWidget->SetTeam(AMUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}

void UAMGameOverWidget::OnResetLevel()
{
	const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}