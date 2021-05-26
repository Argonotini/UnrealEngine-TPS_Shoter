// Shooter Game. By xDedic. All Rights reserved.

#include "Player/AMBaseCharacter.h"
#include "Components/AMCharacterMovementComponent.h"
#include "Components/AMHealthComponent.h"
#include "Components/AMWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

AAMBaseCharacter::AAMBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UAMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UAMHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UAMWeaponComponent>("WeaponComponent");
}

void AAMBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetCapsuleComponent());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &AAMBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AAMBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AAMBaseCharacter::OnGroundLanded);
}

void AAMBaseCharacter::OnHealthChanged(float Health, float HealthDelta) {}

void AAMBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAMBaseCharacter::IsRunnig() const
{
	return false;
}

float AAMBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AAMBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead!"), *GetName());

	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	/** Fix a bug that occurs when our character dies and the zoom does not disappear */
	WeaponComponent->Zoom(false);

	/** Realistic death simulation - (included) */
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	// The sound of death
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AAMBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocituZ = -GetVelocity().Z;
	if (FallVelocituZ < LandedDamageVelocity.X) return;

	const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocituZ);
	TakeDamage(FallDamage, FDamageEvent{}, nullptr, nullptr);

	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s recived landed damage: %f"), *GetName(), FallDamage);
}

void AAMBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void AAMBaseCharacter::TurnOff()
{
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);
	Super::TurnOff();
}

void AAMBaseCharacter::Reset()
{
	WeaponComponent->StopFire();
	WeaponComponent->Zoom(false);
	Super::Reset();
}