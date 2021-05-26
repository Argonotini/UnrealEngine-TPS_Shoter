// Shooter Game. By xDedic. All Rights reserved.

#include "AMGameInstance.h"
#include "Sound/AMSoundFuncLib.h"

void UAMGameInstance::ToggleVolume()
{
    // The main sound switch in the game
    UAMSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}