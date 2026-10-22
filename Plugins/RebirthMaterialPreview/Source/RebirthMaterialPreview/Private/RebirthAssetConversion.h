#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtrTemplates.h"

class UClass;
class UObject;

/**
 * Make Editable for the game's data assets: CharaSpec_<character> (EndAssetDataAsset), anim sets, asset packs, foot
 * attribute sets, data tables, curves and the other plain data the game cooks. The cooked copy in the project becomes a
 * normal editable asset at the same path with every property; references to game assets that are not in the project
 * are kept (RebirthGameReferences). The cooked files go to Saved/RebirthDataAssetBackups/<time>/ with a
 * RestoreManifest.txt. Package Project cooks the editable asset at its game path, so the pak replaces the game's file;
 * duplicates of it (new characters) are packaged at their own paths.
 */
namespace RebirthAssetConversion
{
	void Register();
	void Unregister();

	/** Classes whose cooked form is plain property data (data assets, tables, curves, the game's own data types), so an
	 * editable copy holds everything the game has. Blueprints, meshes, textures, materials, animations, sounds, maps... are not. */
	bool IsPlainDataClass(const UClass* Class);

	/** A cooked asset of a plain-data class (not a blueprint, mesh, texture, material, animation, sound, map...). */
	bool IsConvertible(const UObject* Object);
	TArray<TWeakObjectPtr<UObject>> GetConvertible(const TArray<UObject*>& Objects);

	/** Converts without dialogs; returns how many were converted. OutMessages has one line per asset. */
	int32 MakeEditable(const TArray<UObject*>& Assets, TArray<FString>& OutMessages, FString& OutBackupFolder);

	/**
	 * Saves an editable copy of a cooked data asset at TargetPackageName; the cooked asset stays as it is. For a CharaSpec
	 * data asset copied as CharaSpec_<NewModel>, the entries named <OldModel>_Class/_Data become <NewModel>_Class/_Data
	 * (the game finds them by the ContentsModel of the CharaSpec row).
	 */
	bool MakeEditableCopy(UObject* Cooked, const FString& TargetPackageName, FString& OutMessage);

	/** CharaSpec data asset entries named <OldModel>_Class/_Data are renamed <NewModel>_Class/_Data; returns how many. */
	int32 RenameCharaSpecEntries(UObject* Asset, const FString& OldModel, const FString& NewModel);

	/** Content browser action: confirms (if bConfirm), converts, reports; opens the editor for a single asset. */
	void MakeEditableWithDialog(const TArray<TWeakObjectPtr<UObject>>& Assets, bool bConfirm = true);

	/** Opening a cooked data asset offers to make it editable. True when that was handled (converted or cancelled). */
	bool OfferMakeEditableOnOpen(UObject* Object);

	/** The main asset of a package (/Game/A/B or /Game/A/B.B); loads the package when needed. */
	UObject* FindAsset(const FString& PathOrPackage);

	/**
	 * Saves Editable (an object in a temporary package) as the asset at TargetPackageName. Files already at that path
	 * move to BackupFolder first (listed in InOutManifest); a package already loaded at that path is reloaded from the
	 * new file.
	 */
	bool SaveAsAsset(UObject* Editable, const FString& TargetPackageName, const FString& BackupFolder, TArray<FString>& InOutManifest, FString& OutError);
}
