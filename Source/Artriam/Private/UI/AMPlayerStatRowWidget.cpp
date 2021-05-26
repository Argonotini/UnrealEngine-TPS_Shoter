// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UAMPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void UAMPlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void UAMPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}

void UAMPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void UAMPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UAMPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if (!TeamImage) return;
	TeamImage->SetColorAndOpacity(Color);
}