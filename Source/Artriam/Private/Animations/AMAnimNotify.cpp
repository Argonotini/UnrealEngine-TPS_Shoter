// Shooter Game. By xDedic. All Rights reserved.

#include "Animations/AMAnimNotify.h"

void UAMAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}