// Shooter Game. By xDedic. All Rights reserved.

#include "Pickups/AMHealthPickup.h"
#include "Components/AMHealthComponent.h" 
#include "AMUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool AAMHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = AMUtils::GetAMPlayerComponent<UAMHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}