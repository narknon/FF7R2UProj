#pragma once

#include "CoreMinimal.h"

/**
 * Cooked copies of the game's blueprints and data assets in the project.
 *
 * They are in the project so that new content can use them: a child blueprint derives from one, an edited CharaSpec
 * points at one. Cooking one again does not give back the game's file: references to game assets that are not in the
 * project load as None, a blueprint's compiled logic loses references to members of classes that are not here, and
 * defaults are written against this project's reconstructed native classes. So Package Project leaves them out (see
 * RebirthCookedTextureSkip): packages that use them still cook and keep their references, and the game loads its own
 * files at those paths. Data assets made editable (Make Editable) are normal assets and do cook.
 */
namespace RebirthCookedCopies
{
	/** Long package names of the cooked blueprint and plain-data packages under /Game, sorted. */
	TArray<FName> FindPackages();

	/** The packages of this plugin's self-tests (/Game/RebirthDataObjectTests), which never ship. */
	TArray<FName> FindSelfTestPackages();
}
