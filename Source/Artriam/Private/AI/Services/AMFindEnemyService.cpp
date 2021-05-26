// Shooter Game. By xDedic. All Rights reserved.

#include "AI/Services/AMFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AMUtils.h"
#include "Components/AMAIPerceptionComponent.h"

UAMFindEnemyService::UAMFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UAMFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = AMUtils::GetAMPlayerComponent<UAMAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}