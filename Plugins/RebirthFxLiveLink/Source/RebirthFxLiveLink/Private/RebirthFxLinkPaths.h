#pragma once

#include "CoreMinimal.h"

/** Where FINAL FANTASY VII REBIRTH is installed (its End/Content/Paks folder). */
namespace RebirthFxLinkPaths
{
	/** True for a folder with the game's pakchunk0-*.utoc. */
	bool IsPaksDirectory(const FString& Directory);

	/** The Paks folder for the game folder, End/Content or the Paks folder itself ("" when none of them is). */
	FString ResolvePaksDirectory(const FString& Directory);

	/** The game's Paks folder: the saved choice, then Steam's libraries and the usual places; asks for the game folder if bAsk. */
	FString FindPaksDirectory(bool bAsk);
}
