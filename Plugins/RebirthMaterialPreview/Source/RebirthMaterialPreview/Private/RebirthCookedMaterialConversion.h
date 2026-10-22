#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtrTemplates.h"

class UObject;
class UMaterialInstanceConstant;

/**
 * Turns cooked material instances (retail or cooked mod content loaded in the editor) into normal editable Material
 * Instance assets, in place: the same package path and object name, the same parent, parameter values, static switches
 * and base property overrides, so every mesh and child material keeps referencing it. The cooked .uasset/.uexp files are
 * moved to Saved/RebirthCookedOriginals/<time>/ first (copy them back with the editor closed to undo).
 *
 * A converted RM_Surface instance keeps the recovered in-game shading preview (RebirthRecoveredSurfaces handles editable
 * instances too); the conversion always writes its real parent, switches and overrides.
 */
namespace RebirthCookedMaterialConversion
{
	void Register();
	void Unregister();

	/** The cooked material instances among Objects that can be made editable. */
	TArray<TWeakObjectPtr<UMaterialInstanceConstant>> GetConvertible(const TArray<UObject*>& Objects);

	/** Content browser action: confirms, converts, then reports what happened. */
	void MakeEditableWithDialog(const TArray<TWeakObjectPtr<UMaterialInstanceConstant>>& Instances);

	/** Converts without dialogs; returns how many were converted. OutMessages has one line per asset. */
	int32 MakeEditable(const TArray<UMaterialInstanceConstant*>& Instances, TArray<FString>& OutMessages, FString& OutBackupFolder);
}
