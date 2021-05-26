// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/AMWeaponComponent.h"
#include "AMAIWeaponComponent.generated.h"

UCLASS()
class ARTRIAM_API UAMAIWeaponComponent : public UAMWeaponComponent
{
	GENERATED_BODY()
	
public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};