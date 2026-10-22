#pragma once

#include "CoreMinimal.h"
#include "RebirthDataObjectFormat.h"

class UEndDataObjectBase;
class UObject;

/**
 * Editing and cooking of the game's data objects (CharaSpec and every other UEndDataObjectBase subclass).
 *
 * Installs GEndDataObjectSerializeHandler (EndDataObject module):
 *  - a cooked data object (the game's file, extracted or not) loads its rows and the game's row layout;
 *  - an editable data object saves its rows with the asset (tagged, like a DataTable) and loads them back;
 *  - cooking writes the game's memory-mapped format, byte for byte what the game's own cooker writes for the same rows.
 * When cooking, editable data objects under /Game are added to the cook so Package Project ships them at the game path.
 */
namespace RebirthDataObjects
{
	void Install();
	void Uninstall();

	/** True for data objects loaded from a cooked package. */
	bool IsCookedDataObject(const UObject* Object);

	/** Builds the game's memory image of a data object's rows (what cooking writes). */
	bool BuildImage(const UEndDataObjectBase& DataObject, RebirthDataObjectFormat::FImage& OutImage, FString& OutError);

	/** Replaces the rows and row layout of DataObject with decoded ones (takes the decoded rows). */
	void AssignDecoded(UEndDataObjectBase& DataObject, RebirthDataObjectFormat::FDecoded& Decoded);

	/** The game's row layout is known (imported from the game or loaded from a cooked file), so the data object can be cooked. */
	bool HasGameLayout(const UEndDataObjectBase& DataObject);
}
