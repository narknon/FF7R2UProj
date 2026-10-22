#pragma once

#include "CoreMinimal.h"

class FArchive;
class UEndDataObjectBase;

/**
 * Optional serialization for data objects, installed by an editor plugin (RebirthMaterialPreview).
 *
 * The handler reads the game's memory-mapped format when a cooked data object is loaded, saves the rows with editor
 * assets (so they can be edited and saved in the editor), and writes the game's memory-mapped format when cooking.
 * It returns true when it serialized the object; UEndDataObjectBase::Serialize runs its built-in code otherwise.
 */
typedef bool (*FEndDataObjectSerializeHandler)(UEndDataObjectBase& DataObject, FArchive& Ar);

extern ENDDATAOBJECT_API FEndDataObjectSerializeHandler GEndDataObjectSerializeHandler;
