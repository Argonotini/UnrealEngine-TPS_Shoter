// Shooter Game. By xDedic. All Rights reserved.

#include "AI/Services/AMChangeWeaponService.h"
#include "Components/AMWeaponComponent.h"
#include "AIController.h"
#include "AMUtils.h"

UAMChangeWeaponService::UAMChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void UAMChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const auto Controller = OwnerComp.GetAIOwner())
	{
		const auto WeaponComponent = AMUtils::GetAMPlayerComponent<UAMWeaponComponent>(Controller->GetOwner());
		if (WeaponComponent && Probality > 0 && FMath::Rand() <= Probality)
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}