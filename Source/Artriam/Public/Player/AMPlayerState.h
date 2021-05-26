// Shooter Game. By xDedic. All Rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AMPlayerState.generated.h"

UCLASS()
class ARTRIAM_API AAMPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	void SetTeamID(int32 ID) { TeamID = ID; }
	int32 GetTeamID() const { return TeamID; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() const { return TeamColor; }

	// Number of kills
	void AddKill() { ++KillsNum; }
	int32 GetKillsNum() const { return KillsNum; }

	// Number of deaths
	void AddDeath() { ++DeathsNum; }
	int32 GetDeathsNum() const { return DeathsNum; }

	void LogInfo();

private:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathsNum = 0;
};
