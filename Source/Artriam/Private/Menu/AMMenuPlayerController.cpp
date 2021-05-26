// Shooter Game. By xDedic. All Rights reserved.


#include "Menu/AMMenuPlayerController.h"

void AAMMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}