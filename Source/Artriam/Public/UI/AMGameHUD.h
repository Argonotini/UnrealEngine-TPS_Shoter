// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AMCoreTypes.h"
#include "AMGameHUD.generated.h"

class UAMBaseWidget;

UCLASS()
class ARTRIAM_API AAMGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EAMMatchState, UAMBaseWidget*> GameWidgets;

	UPROPERTY()
	UAMBaseWidget* CurrentWidget = nullptr;

	void DrawCrossHair();
	void OnMatchStateChanged(EAMMatchState State);
};