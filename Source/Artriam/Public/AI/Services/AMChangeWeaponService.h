// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AMChangeWeaponService.generated.h"

UCLASS()
class ARTRIAM_API UAMChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	UAMChangeWeaponService();

protected:
	// The probability with which the AI can change weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probality = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
