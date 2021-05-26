// Shooter Game. By xDedic. All Rights reserved.

#include "AI/Decorators/AMHealthPercentDecorator.h"
#include "AIController.h"
#include "AMUtils.h"
#include "Components/AMHealthComponent.h"

UAMHealthPercentDecorator::UAMHealthPercentDecorator()
{
	NodeName = "Health Percent";
}

bool UAMHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = AMUtils::GetAMPlayerComponent<UAMHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
