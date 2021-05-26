// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AMCoreTypes.h"
#include "AMPlayerController.generated.h"

class UAMRespawnComponent;

UCLASS()
class ARTRIAM_API AAMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAMPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAMRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnMatchStateChanged(EAMMatchState State);
	
	// Mute the sound when a key is pressed
	void OnMuteSound();
};