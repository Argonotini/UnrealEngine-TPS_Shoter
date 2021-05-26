// Shooter Game. By xDedic. All Rights reserved.

#include "Player/AMPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogAMPlayerState, All, All);

void AAMPlayerState::LogInfo()
{
	UE_LOG(LogAMPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
