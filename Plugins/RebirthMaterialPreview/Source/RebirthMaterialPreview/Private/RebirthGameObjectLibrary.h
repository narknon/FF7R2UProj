#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthGameObjectLibrary.generated.h"

// Game assets for edited assets to point at, also the ones this project does not have (the RebirthSkelCompat data object's
// character and weapon swaps call these through reflection to set a pack's blueprint, voice and effects).
UCLASS()
class URebirthGameObjectLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// The object at ObjectPath (/Game/Folder/Package.Object; Package.Name_C for a blueprint class): this project's own when it
	// has the package, else an in-memory stand-in for the game's (never saved or cooked: a reference to it is kept and
	// resolves to the game's asset in game). ClassPath: its class, e.g. /Script/SQEXSEAD.SQEXSEADSound, or
	// /Script/Engine.BlueprintGeneratedClass for a blueprint class. Null, with the reason in Message, when there is none.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Game Assets")
	static UObject* GetGameObject(const FString& ObjectPath, const FString& ClassPath, FString& Message);

	// The game's packages whose name is ShortName (e.g. VO_PC0000_02_Cloud_Insanity), sorted; empty when the game's paks
	// cannot be read.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Game Assets")
	static TArray<FString> FindGamePackages(const FString& ShortName);
};
