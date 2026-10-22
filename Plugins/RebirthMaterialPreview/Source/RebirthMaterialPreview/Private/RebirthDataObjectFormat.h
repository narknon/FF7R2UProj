#pragma once

#include "CoreMinimal.h"
#include "Templates/Function.h"

class FProperty;
class UScriptStruct;

/**
 * The game's memory-mapped data object format (UEndDataObjectBase subclasses such as CharaSpec).
 *
 * A cooked data object stores one frozen memory image:
 *   root:  TMemoryImageMap<FName, int32> row map (row name -> row index, a TSet with a hash table),
 *          TArray of {FName field, int32 type code} (the row layout), TArray of rows.
 *   then every array/string the rows point to, one section per allocation in depth-first order; sections without
 *   pointers that are byte-identical (including their names) are stored once.
 * Names inside the image are zero and listed separately as (name, offsets) patches. Row names are hashed with the low
 * 32 bits of CityHash64 of the lower-case name plus the name number.
 *
 * Encode() reproduces the game's files byte for byte from their decoded rows (verified against every data object in
 * the game). The row layout (field order and type codes) is the game's and cannot be derived from this project's row
 * structs; it is read from a game file and kept with the asset.
 */
namespace RebirthDataObjectFormat
{
	enum ETypeCode : int32
	{
		TypeBool = 1,
		TypeUInt8 = 2,
		TypeInt8 = 3,
		TypeUInt16 = 4,
		TypeInt16 = 5,
		TypeUInt32 = 6,
		TypeInt32 = 7,
		TypeInt64 = 8,
		TypeFloat = 9,
		TypeString = 10,
		TypeName = 11,
	};

	const TCHAR* TypeCodeName(int32 TypeCode);

	/** One row field in the game's layout, matched to the row struct of this project. */
	struct FField
	{
		FName Name;
		int32 TypeCode = 0;
		bool bArray = false;
		const FProperty* Property = nullptr;      // the row struct's property
		const FProperty* ValueProperty = nullptr; // Property, or the inner property of an array
		int32 Offset = 0;                         // in the game's row
	};

	struct FLayout
	{
		TArray<FField> Fields;
		int32 RowSize = 0;
		int32 RowAlignment = 1;

		/** Matches the game's field list to RowStruct. Fails when a field is missing or has another type in this project. */
		bool Build(const UScriptStruct* RowStruct, const TArray<FName>& FieldNames, const TArray<int32>& FieldTypes, FString& OutError);
	};

	/** A frozen image plus the names to patch into it (sorted, offsets ascending). */
	struct FImage
	{
		TArray<uint8> Content;
		TArray<TPair<FName, TArray<uint32>>> Names;
	};

	/** Decoded rows. Each row is FMemory::Malloc'ed and initialized for the row struct; the caller owns them (see FreeRows). */
	struct FDecoded
	{
		TArray<FName> FieldNames;
		TArray<int32> FieldTypes;
		TArray<FName> RowNames;
		TArray<uint8*> Rows;
	};

	/** The name stored at an offset in the content (NAME_None when there is none). */
	typedef TFunctionRef<FName(uint32 Offset)> FNameAt;

	bool Decode(const uint8* Content, int64 ContentSize, FNameAt NameAt, const UScriptStruct* RowStruct, FDecoded& Out, FString& OutError);

	void FreeRows(const UScriptStruct* RowStruct, TArray<uint8*>& Rows);

	bool Encode(const FLayout& Layout, const TArray<FName>& RowNames, const TArray<const uint8*>& Rows, FImage& Out, FString& OutError);

	/** The hash the game's row map uses for a row name. */
	uint32 HashRowName(FName Name);

	/** Number of hash buckets the game's row map uses for NumRows rows. */
	int32 HashBucketCount(int32 NumRows);
}
