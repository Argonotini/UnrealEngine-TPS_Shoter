#pragma once

#include "AMCoreTypes.generated.h"

// Weapon
class AAMBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, AAMBaseWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	/** Number of cartridges */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
	int32 Bullets;

	/** Number of magazines for the current weapon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons", meta = (EditCondition = "!Infinite"))
	int32 Clips;

	/** The arsenal of weapons is over */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
	bool Infinite;

};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	// Weapon class definitions
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AAMBaseWeapon> WeaponClasses;

	// Mounting Recharge
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	// Weapon icon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* MainIcon;

	// Aim icon depending on the choice of weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* CrossHairIcon;
};

// Health
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

// VFX Effect
class UNiagaraSystem;
class USoundCue;

USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	// Decal material
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;

	// Decal size
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);

	// Decal lifetime
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	// Alpha channel lifetime
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;

	// Basic pointer to Sound-Cue
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* Sound;
};

// Game
USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	/** Number of players */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
	int32 PlayersNum = 2;

	/** Number of rounds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundsNum = 4;

	/** Rounds time */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "1000"))
	int32 RoundTime = 10; // in seconds

	// Change the color of command meshes
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	// Base team color
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLinearColor> TeamColors;

	// Recovery time
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
	int32 RespawnTime = 5;  // in seconds
};

// Game States
UENUM(BlueprintType)
enum class EAMMatchState : uint8
{
	WaitingToStart = 0,	// Waiting for the start
	InProgress,			// The game is in progress
	Pause,				// Pause game
	GameOver			// Game over
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EAMMatchState);

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_USTRUCT_BODY()

	// Card name (Must be identical with the name of the called level)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName LevelName = NAME_None;

	// Name of the map in the menu
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	FName LevelDisplayName = NAME_None;

	// Menu icon in the menu
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
	UTexture2D* LevelThumb;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);