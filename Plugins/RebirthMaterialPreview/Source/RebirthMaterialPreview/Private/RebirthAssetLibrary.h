#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RebirthAssetLibrary.generated.h"

// Editor scripting (Python, Blueprint utilities) for the game's data assets and blueprints in this project: make
// editable, inspect and change properties, duplicate, create child blueprints, and write the cooked form to a file.
// Paths are package names (/Game/A/B) or object paths (/Game/A/B.B).
UCLASS()
class URebirthAssetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Makes a cooked data asset in the project editable in place. References to game assets that are not in the
	// project are kept.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static bool MakeAssetEditable(const FString& PathOrPackage, FString& Message);

	// Saves an editable copy of a cooked data asset at TargetPackageName; the cooked asset stays as it is. Copying a
	// CharaSpec data asset as CharaSpec_<NewModel> renames its <OldModel>_Class/_Data entries after NewModel.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static bool MakeEditableCopy(const FString& PathOrPackage, const FString& TargetPackageName, FString& Message);

	// Cooked data assets (plain-data classes) in the project under Folder (empty: all of /Game).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static TArray<FString> ListCookedDataAssets(const FString& Folder);

	// Packages the cooked-load guard had to skip parts of since the editor started ("package: details").
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static TArray<FString> GetSafeLoadReport();

	// Object paths the asset (and its subobjects) reference outside its own package, /Script objects excluded.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static TArray<FString> GetAssetReferences(const FString& PathOrPackage);

	// The packages that stand in for game assets that are not in the project.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static TArray<FString> GetGameReferencePackages();

	// Creates the stand-ins a package needs; returns how many objects were created.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static int32 EnsureGameReferences(const FString& PackageName);

	// How the project's file of a package reads without loading it ("cooked, 33 imports, 1 exports"), or why it cannot.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static FString DescribePackageHeader(const FString& PackageName);

	// A property of the asset as text (for a blueprint: of its class defaults). Empty when there is no such property.
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static FString GetAssetProperty(const FString& PathOrPackage, const FString& PropertyName);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static bool SetAssetProperty(const FString& PathOrPackage, const FString& PropertyName, const FString& Value, FString& Message);

	// A saved copy of an editable asset at TargetPackageName (for example a new character's CharaSpec data asset).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static bool DuplicateAsset(const FString& PathOrPackage, const FString& TargetPackageName, FString& Message);

	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static bool SaveAsset(const FString& PathOrPackage, FString& Message);

	// Saves the asset the way cooking does (WindowsNoEditor) to Filename (.uasset, with its .uexp beside it).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Assets")
	static bool CookAssetToFile(const FString& PathOrPackage, const FString& Filename, FString& Message);

	// The game's blueprint classes in the project under Folder (empty: all of /Game).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Blueprints")
	static TArray<FString> ListGameBlueprints(const FString& Folder);

	// Creates and saves an editable child blueprint of a game blueprint (class path or package name).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Blueprints")
	static bool CreateChildBlueprint(const FString& ParentClassOrPackage, const FString& TargetPackageName, FString& Message);

	// The parent class path of a blueprint (editable or game).
	UFUNCTION(BlueprintCallable, Category = "Rebirth|Blueprints")
	static FString GetBlueprintParent(const FString& PathOrPackage);
};
