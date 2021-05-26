// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/AMBasePickup.h"
#include "AMAmmoPickup.generated.h"

class AAMBaseWeapon;

UCLASS()
class ARTRIAM_API AAMAmmoPickup : public AAMBasePickup
{
	GENERATED_BODY()
	
protected:
	/** The number of shops a character can take */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;

	/** Selecting the type of weapon to determine the magazines */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<AAMBaseWeapon> WeaponType;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};