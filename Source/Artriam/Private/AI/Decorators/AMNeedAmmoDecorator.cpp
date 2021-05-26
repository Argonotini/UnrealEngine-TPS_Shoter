// Shooter Game. By xDedic. All Rights reserved.

#include "AI/Decorators/AMNeedAmmoDecorator.h"
#include "AIController.h"
#include "AMUtils.h"
#include "Components/AMWeaponComponent.h"

UAMNeedAmmoDecorator::UAMNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool UAMNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory) const
{
	const auto Controller = OwerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = AMUtils::GetAMPlayerComponent<UAMWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
}