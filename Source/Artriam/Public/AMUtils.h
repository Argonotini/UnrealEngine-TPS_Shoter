#pragma once
#include "Player/AMPlayerState.h"

// General purpose helper iterator
class AMUtils
{
public:
	template <typename T>
	static T* GetAMPlayerComponent(AActor* SomeActor)
	{
		if (!SomeActor) return nullptr;

		const auto Component = SomeActor->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}

	// Checking for a command
	bool static AreEnemies(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const auto PlayerState1 = Cast<AAMPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<AAMPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}
	static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }
};