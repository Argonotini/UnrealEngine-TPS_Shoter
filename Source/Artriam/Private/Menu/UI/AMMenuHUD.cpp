// Shooter Game. By xDedic. All Rights reserved.

#include "Menu/UI/AMMenuHUD.h"
#include "UI/AMBaseWidget.h"

void AAMMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (const auto MenuWidget = CreateWidget<UAMBaseWidget>(GetWorld(), MenuWidgetClass))
	{
		MenuWidget->AddToViewport();
		MenuWidget->Show();
	}
}