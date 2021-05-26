// Shooter Game. By xDedic. All Rights reserved.

#include "UI/AMSpectatorWidget.h"
#include "AMUtils.h"
#include "Components/AMRespawnComponent.h"

bool UAMSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto Respawncomponent = AMUtils::GetAMPlayerComponent<UAMRespawnComponent>(GetOwningPlayer());
	if (!Respawncomponent || !Respawncomponent->IsRespawnInProgress()) return false;

	CountDownTime = Respawncomponent->GetRespawnCountDown();
	return true;
}