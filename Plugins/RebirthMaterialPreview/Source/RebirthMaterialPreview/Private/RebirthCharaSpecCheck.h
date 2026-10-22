#pragma once

#include "CoreMinimal.h"

class UEndDataObjectBase;

/**
 * Checks CharaSpec rows for references the game cannot resolve. The game waits on the loading screen forever when one
 * of them is missing, so this runs before such rows are saved or packaged:
 *  - ContentsModel M: the data asset /Game/DataAsset/Game/CharaSpec/CharaSpec_M must exist (an editable one in this
 *    project, or the game's own) with entries named M_Class and M_Data;
 *  - AnimationSetParentFolder F with AnimationSetList: an anim set package /Game/Motion/.../F/<set> for every set;
 *  - NoBattleCharaSpec, ReserveCharaSpec, EquipmentCharaSpecList, SharedCharaSpecList: rows of the same table.
 * Only rows that are new or differ from the game's own table are checked (the game's rows include a few unused ones
 * with dangling references).
 */
namespace RebirthCharaSpecCheck
{
	/** A data object whose rows are the game's CharaSpec rows (FEndDataTableCharaSpec). */
	bool IsCharaSpecTable(const UEndDataObjectBase& DataObject);

	/** Rows that are new or differ from the game's table (every row when the game's table cannot be read). */
	TArray<FName> GetChangedRows(const UEndDataObjectBase& DataObject);

	/** One line per problem ("Row: what is wrong"). Rows empty = the changed rows. */
	TArray<FString> Check(const UEndDataObjectBase& DataObject, const TArray<FName>& Rows = TArray<FName>());

	/** Check() on the changed rows; problems go to the log (and an editor notification when bNotify). */
	TArray<FString> CheckAndReport(const UEndDataObjectBase& DataObject, bool bNotify);

	/** Checks CharaSpec tables after they are saved in the editor. */
	void Register();
	void Unregister();
}
