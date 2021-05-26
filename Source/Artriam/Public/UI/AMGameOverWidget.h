// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/AMBaseWidget.h"
#include "AMCoreTypes.h"
#include "AMGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class ARTRIAM_API UAMGameOverWidget : public UAMBaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(EAMMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();
};