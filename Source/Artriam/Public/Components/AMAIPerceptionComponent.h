// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AMAIPerceptionComponent.generated.h"

UCLASS()
class ARTRIAM_API UAMAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetClosestEnemy() const;
	
};