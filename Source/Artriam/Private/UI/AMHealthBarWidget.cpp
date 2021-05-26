// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UAMHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar) return;

	const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))  //
		? ESlateVisibility::Hidden
		: ESlateVisibility::Visible;
	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}