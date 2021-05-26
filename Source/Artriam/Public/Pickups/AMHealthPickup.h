// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/AMBasePickup.h"
#include "AMHealthPickup.generated.h"

UCLASS()
class ARTRIAM_API AAMHealthPickup : public AAMBasePickup
{
	GENERATED_BODY()

protected:
	// HP value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "1000.0"))
	float HealthAmount = 100.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};