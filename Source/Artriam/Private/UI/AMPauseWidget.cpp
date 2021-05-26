// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"

void UAMPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UAMPauseWidget::OnClearPause);
	}
}

void UAMPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}