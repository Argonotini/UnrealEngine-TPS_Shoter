// Shooter Game. By xDedic. All Rights reserved.

#include "Components/AMCharacterMovementComponent.h"
#include "Player/AMBaseCharacter.h"

float UAMCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AAMBaseCharacter* Player = Cast<AAMBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunnig() ? MaxSpeed * RunModifier : MaxSpeed;;
}