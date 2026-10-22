#pragma once

#include "CoreMinimal.h"

class UBlueprint;
class UClass;

/**
 * Blueprints of the game copied into the project (cooked: classes without graphs, invisible to the content browser).
 *
 *  - Game Blueprints window (File > Rebirth, and on content browser folders): lists them, shows a blueprint's defaults
 *    and components read-only, and creates child blueprints.
 *  - A child blueprint is a normal editable blueprint whose parent is the game's class: it inherits the game's
 *    components, defaults and compiled logic; override any default or component (mesh, materials, anim class...) and
 *    add your own nodes. Package Project cooks it like any blueprint; in the game it runs on top of the game's class.
 * The game blueprint and its references to game assets that are not in the project are kept (RebirthGameReferences).
 */
namespace RebirthBlueprintTools
{
	void Register();
	void Unregister();

	struct FGameBlueprint
	{
		FString PackageName;
		FString ClassPath;
		FName GeneratedClassType;
		FString ParentClassPath;
	};

	/** Cooked blueprint classes in the project under Folder (a /Game path; empty for all of /Game), sorted by package. */
	void FindGameBlueprints(const FString& Folder, TArray<FGameBlueprint>& OutBlueprints);

	/** Loads a game blueprint class (class path or package name), keeping its references to game assets not in the project. */
	UClass* LoadGameBlueprintClass(const FString& ClassPathOrPackage, FString& OutError);

	/** Creates and saves an editable blueprint at PackageName whose parent is ParentClass (anim blueprints get the parent's skeleton). */
	UBlueprint* CreateChildBlueprint(UClass* ParentClass, const FString& PackageName, FString& OutError);

	void OpenGameBlueprintsWindow(const FString& Folder = FString());
}
