#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtrTemplates.h"

class UEndDataObjectBase;
class UObject;

/**
 * Editor workflow for the game's data objects (CharaSpec and the rest):
 *  - Make Editable: a cooked data object in the project (an extracted game file) becomes an editable asset at the same
 *    path, with every row and the game's row layout. The cooked files go to Saved/RebirthDataObjectBackups/.
 *  - Import from Game: reads a data object from the game's Paks and creates the editable asset at its game path.
 * Editable data objects open in the project's Data Object table editor (add, duplicate, rename, delete and edit rows).
 * Package Project cooks them in the game's format at the same path, so the pak replaces the game's file.
 */
namespace RebirthDataObjectEditing
{
	void Register();
	void Unregister();

	bool IsConvertible(const UObject* Object);
	TArray<TWeakObjectPtr<UEndDataObjectBase>> GetConvertible(const TArray<UObject*>& Objects);

	/**
	 * The data object at PathOrPackage: an object path (/Game/A/B.B) or a package name (/Game/A/B). For a package name it is
	 * the object named after the package, else the package's data object (a copied game file keeps the game's object name).
	 * Loads the package when needed.
	 */
	UEndDataObjectBase* FindDataObject(const FString& PathOrPackage);

	/** Content browser action: confirms (if bConfirm), converts, reports; opens the table editor for a single data object. */
	void MakeEditableWithDialog(const TArray<TWeakObjectPtr<UEndDataObjectBase>>& DataObjects, bool bConfirm = true);

	/** Converts without dialogs; returns how many were converted. OutMessages has one line per data object. */
	int32 MakeEditable(const TArray<UEndDataObjectBase*>& DataObjects, TArray<FString>& OutMessages, FString& OutBackupFolder);

	/**
	 * Creates (or replaces) the editable asset for a game data object, e.g. /Game/DataObject/Resident/CharaSpec.
	 * TargetPackageName defaults to the game path (which is what Package Project needs to replace the game's file).
	 */
	bool ImportFromGame(const FString& GamePackageName, const FString& PaksDirectory, FString& OutMessage, const FString& TargetPackageName = FString());

	/** Tools menu: pick a data object from the game's Paks and import it. */
	void OpenImportDialog();

	/** Opening a cooked data object offers to make it editable. True when that was handled (converted or cancelled). */
	bool OfferMakeEditableOnOpen(UObject* Object);
}
