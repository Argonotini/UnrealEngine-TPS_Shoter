// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/AMBaseWeapon.h"
#include "AMLauncherWeapon.generated.h"

class AAMProjectile;
class USoundCue;

UCLASS()
class ARTRIAM_API AAMLauncherWeapon : public AAMBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AAMProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* NoAmmoSound;

	virtual void MakeShot() override;
	
};
