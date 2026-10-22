#pragma once

#include "CoreMinimal.h"

class UClass;
class UObject;
class UPackage;

/**
 * References to game assets that are not in this project.
 *
 * An editable asset made from a game file usually points at things the project does not contain: another character's
 * blueprint, its motion sets, a sound bank, a camera pack. Normally those references load as None, and saving or cooking
 * the asset then drops them, so the packaged asset no longer works in the game.
 *
 * Before such an asset loads, every object it imports from a package that is missing here is created in memory as a
 * stand-in with the same path and class as in the game (blueprint classes get the game's own super class when the
 * game's packages can be read). Loading, editing, saving and cooking then keep every reference, and in the game they
 * resolve to the game's own assets. Stand-ins have no file: they are never saved (saving them is refused) and never
 * cooked (the cooker only cooks packages that exist on disk).
 *
 * Assets saved by this editor get stand-ins automatically whenever they load. Cooked game copies get them only when a
 * tool asks (EnsureForPackage, e.g. Make Editable), so the game copies already in the project load exactly as before.
 */
namespace RebirthGameReferences
{
	void Install();
	void Uninstall();

	/** Creates the stand-ins PackageName needs (also later, whenever it reloads). Returns how many objects were created. */
	int32 EnsureForPackage(const FString& PackageName, TArray<FString>* OutMissingPackages = nullptr);

	bool IsStandInPackage(const UPackage* Package);
	bool IsStandIn(const UObject* Object);

	/** The stand-in packages that exist now, sorted. */
	TArray<FString> GetStandInPackageNames();

	/**
	 * The object at ObjectPath (/Game/Folder/Package.Object, Package.Name_C for a blueprint class) for an edited asset to point
	 * at: this project's own when it has the package, else a stand-in made like the stand-ins of an asset's imports (when the
	 * game's paks can be read, only for a package they have). Class: the object's class (UBlueprintGeneratedClass for a
	 * blueprint class). Null, with the reason in OutError, when there is no such object.
	 */
	UObject* FindOrStandIn(const FString& ObjectPath, UClass* Class, FString& OutError);
}
