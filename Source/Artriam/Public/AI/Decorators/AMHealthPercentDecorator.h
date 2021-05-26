// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "AMHealthPercentDecorator.generated.h"

UCLASS()
class ARTRIAM_API UAMHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UAMHealthPercentDecorator();
	
protected:
	// If equal to the condition or less, AI will try to search for a pickup in the range of sight and pick it up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
