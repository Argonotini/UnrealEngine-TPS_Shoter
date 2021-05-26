// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AMAIController.generated.h"

class UAMAIPerceptionComponent;
class UAMRespawnComponent;

UCLASS()
class ARTRIAM_API AAMAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAMAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAMAIPerceptionComponent* AMAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAMRespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	// Can be called several times during the game and in the controller can change the number of times
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;
};