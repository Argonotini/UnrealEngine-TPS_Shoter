// Shooter Game. By xDedic. All Rights reserved.

#include "Menu/AMMenuGameModeBase.h"
#include "Menu/AMMenuPlayerController.h"
#include "Menu/UI/AMMenuHUD.h"

AAMMenuGameModeBase::AAMMenuGameModeBase()
{
	PlayerControllerClass = AAMMenuPlayerController::StaticClass();
	HUDClass = AAMMenuHUD::StaticClass();
}