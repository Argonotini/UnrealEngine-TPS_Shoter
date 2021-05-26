// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AMGameDataWidget.generated.h"

class AAMGameModeBase;
class AAMPlayerState;

UCLASS()
class ARTRIAM_API UAMGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	AAMGameModeBase* GetAMGameMode() const;
	AAMPlayerState* GetAMPlayerState() const;
};