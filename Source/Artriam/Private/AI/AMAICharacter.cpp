// Shooter Game. By xDedic. All Rights reserved.

#include "AI/AMAICharacter.h"
#include "AI/AMAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AMAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/AMHealthBarWidget.h"
#include "Components/AMHealthComponent.h"

AAMAICharacter::AAMAICharacter(const FObjectInitializer& ObjInit)
	:Super(ObjInit.SetDefaultSubobjectClass<UAMAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AAMAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AAMAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void AAMAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHealthWidgetVisibility();
}

void AAMAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AMController = Cast<AAIController>(Controller);
	if (AMController && AMController->BrainComponent)
	{
		AMController->BrainComponent->Cleanup();
	}
}

void AAMAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto HealthBarWidget = Cast<UAMHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AAMAICharacter::UpdateHealthWidgetVisibility()
{
	if (!GetWorld() ||                              //
		!GetWorld()->GetFirstPlayerController() ||  //
		!GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
		return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}