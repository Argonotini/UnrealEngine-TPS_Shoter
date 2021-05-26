// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AMBaseCharacter.generated.h"

class UAMHealthComponent;
class UAMWeaponComponent;
class USoundCue;

UCLASS()
class ARTRIAM_API AAMBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAMBaseCharacter(const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAMHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAMWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	// Time to respawn after death
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	/** Drop height */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	/** Inflicted damage when falling */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	// The name of the key in the material to be changed
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

	// Pointer to Sound Cue
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* DeathSound;

	virtual void BeginPlay() override;
	virtual void OnDeath();
	virtual void OnHealthChanged(float Health, float HealthDelta);

public:
	virtual void Tick(float DeltaTime) override;

	// Stop firing All!
	virtual void TurnOff() override;
	virtual void Reset() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunnig() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	void SetPlayerColor(const FLinearColor& Color);

private:
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};