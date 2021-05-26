// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AMCoreTypes.h"
#include "AMWeaponComponent.generated.h"

class AAMBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARTRIAM_API UAMWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAMWeaponComponent();

	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<AAMBaseWeapon> WeaponType, int32 ClipsAmount);
	bool NeedAmmo(TSubclassOf<AAMBaseWeapon> WeaponType);

	/** Optical zoom
	* Calls up the zoom function of the current weapon.
	*/
	void Zoom(bool Enabled);
	
protected:
	/** Sleeping weapon class
	*  
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY()
	AAMBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<AAMBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

	bool CanFire() const;
	bool CanEquip() const;

	/** Weapon equipment (pump weapons into hand) */
	void EquipWeapon(int32 WeaponIndex);

private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	void InitAnimations();
	void SpawnWeapons();
	void AttachWeaponToSocket(AAMBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	/** Play cut to change weapons */
	void PlayAnimMontage(UAnimMontage* Animation);

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanReload() const;

	void OnClipEmpty(AAMBaseWeapon* ClipEmptyWeapon);
	void ChangeClip();
};