// Shooter Game. By xDedic. All Rights reserved.

#include "Weapon/Components/AMWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

UAMWeaponFXComponent::UAMWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAMWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto ImpactData = DefaultInpactData;

	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}

	// Niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),//
	ImpactData.NiagaraEffect,//
	Hit.ImpactPoint,//
	Hit.ImpactNormal.Rotation());

	// Decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),//
	ImpactData.DecalData.Material,//
	ImpactData.DecalData.Size,//
	Hit.ImpactPoint,//
	Hit.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	// Sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.Sound, Hit.ImpactPoint);
}