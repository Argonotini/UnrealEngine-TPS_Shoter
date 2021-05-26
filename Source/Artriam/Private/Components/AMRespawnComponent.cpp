// Shooter Game. By xDedic. All Rights reserved.

#include "Components/AMRespawnComponent.h"
#include "AMGameModeBase.h"

UAMRespawnComponent::UAMRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAMRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UAMRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void UAMRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AAMGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}

bool UAMRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

