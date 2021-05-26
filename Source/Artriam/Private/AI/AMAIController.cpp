// Shooter Game. By xDedic. All Rights reserved.

#include "AI/AMAIController.h"
#include "AI/AMAICharacter.h"
#include "Components/AMAIPerceptionComponent.h"
#include "Components/AMRespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAMAIController::AAMAIController()
{
	AMAIPerceptionComponent = CreateDefaultSubobject<UAMAIPerceptionComponent>("AMAIPerceptionComponent");
	SetPerceptionComponent(*AMAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<UAMRespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void AAMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (const auto AMCharacter = Cast<AAMAICharacter>(InPawn))
	{
		RunBehaviorTree(AMCharacter->BehaviorTreeAsset);
	}
}

void AAMAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetFocus(GetFocusOnActor());
}

AActor* AAMAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}