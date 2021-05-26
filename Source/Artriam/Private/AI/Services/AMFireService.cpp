// Shooter Game. By xDedic. All Rights reserved.

#include "AI/Services/AMFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AMWeaponComponent.h"
#include "AMUtils.h"

UAMFireService::UAMFireService()
{
	NodeName = "Fire";
}

void UAMFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (const auto Controller = OwnerComp.GetAIOwner())
	{
		if (const auto WeaponComponent = AMUtils::GetAMPlayerComponent<UAMWeaponComponent>(Controller->GetPawn()))
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}