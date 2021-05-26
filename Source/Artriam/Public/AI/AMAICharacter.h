// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/AMBaseCharacter.h"
#include "AMAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class ARTRIAM_API AAMAICharacter : public AAMBaseCharacter
{
	GENERATED_BODY()

public:
	AAMAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;

	// Maximum visibility for picking up a pickup
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float HealthVisibilityDistance = 1000.f;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};