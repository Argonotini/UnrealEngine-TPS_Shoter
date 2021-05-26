// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMGameDataWidget.h"
#include "AMGameModeBase.h"
#include "Player/AMPlayerState.h"

int32 UAMGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetAMGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UAMGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetAMGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UAMGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetAMGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

AAMGameModeBase* UAMGameDataWidget::GetAMGameMode() const
{
	return GetWorld() ? Cast<AAMGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AAMPlayerState* UAMGameDataWidget::GetAMPlayerState() const
{
	return GetOwningPlayer() ? Cast<AAMPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}