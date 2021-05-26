// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMGoToMenuWidget.h"
#include "Components/Button.h"
#include "AMGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogAMGoToMenuWidget, All, All);

void UAMGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UAMGoToMenuWidget::OnGoToMenu);
	}
}

void UAMGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) return;

	const auto AMGameInstance = GetWorld()->GetGameInstance<UAMGameInstance>();
	if (!AMGameInstance) return;

	if (AMGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogAMGoToMenuWidget, Error, TEXT("Menu level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, AMGameInstance->GetMenuLevelName());
}