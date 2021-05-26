// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AMSoundFuncLib.generated.h"

class USoundClass;

UCLASS()
class ARTRIAM_API UAMSoundFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Sets the volume for the desired Sound-Class
	UFUNCTION(BlueprintCallable)
	static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	// Sets the volume to zero if it is not zero, and vice versa
	UFUNCTION(BlueprintCallable)
	static void ToggleSoundClassVolume(USoundClass* SoundClass);
};