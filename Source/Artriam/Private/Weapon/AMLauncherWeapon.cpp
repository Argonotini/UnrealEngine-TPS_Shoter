// Shooter Game. By xDedic. All Rights reserved.

#include "Weapon/AMLauncherWeapon.h"
#include "Weapon/AMProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void AAMLauncherWeapon::StartFire()
{
	MakeShot();
}

void AAMLauncherWeapon::MakeShot()
{
	if (!GetWorld()) return;

	if (IsAmmoEmpty())
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AAMProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAMProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
	SpawnMuzzleFX();

	/**
	 * @param SpawnSoundAttached - playing the sound of a shot.
	 * FireSound - sound;
	 * WeaponMesh - component to which the sound is attached;
	 * MuzzleSocketName socket name (in our case, the sound coordinates will be relative to the muzzle)).
	 */
	UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}