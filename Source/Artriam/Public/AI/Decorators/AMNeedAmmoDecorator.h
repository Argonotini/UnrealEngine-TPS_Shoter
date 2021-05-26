// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "AMNeedAmmoDecorator.generated.h"

class AAMBaseWeapon;

UCLASS()
class ARTRIAM_API UAMNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UAMNeedAmmoDecorator();

protected:
	// Determining the type of weapon and checking if there are not enough cartridges to a full clip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AAMBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwerComp, uint8* NodeMemory) const override;
};