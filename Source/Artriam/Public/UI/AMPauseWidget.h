// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/AMBaseWidget.h"
#include "AMPauseWidget.generated.h"

class UButton;

UCLASS()
class ARTRIAM_API UAMPauseWidget : public UAMBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnClearPause();
};