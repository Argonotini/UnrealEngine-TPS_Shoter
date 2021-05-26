// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AMFindEnemyService.generated.h"

UCLASS()
class ARTRIAM_API UAMFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
	UAMFindEnemyService();

protected:
	// Service function for finding an enemy character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};