// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AMBaseWidget.generated.h"

class USoundCue;

UCLASS()
class ARTRIAM_API UAMBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Show();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* OpenSound;
};