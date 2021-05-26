// Shooter Game. By xDedic. All Rights reserved.

#include "Pickups/AMAmmoPickup.h"
#include "Components/AMHealthComponent.h"
#include "Components/AMWeaponComponent.h"
#include "AMUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AAMAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = AMUtils::GetAMPlayerComponent<UAMHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = AMUtils::GetAMPlayerComponent<UAMWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}