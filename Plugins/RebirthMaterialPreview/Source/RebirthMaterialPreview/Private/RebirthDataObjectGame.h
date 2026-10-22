#pragma once

#include "CoreMinimal.h"
#include "RebirthDataObjectFormat.h"

class UClass;

/**
 * Reads data objects straight from the game's IoStore containers (End/Content/Paks/pakchunk*.utoc/.ucas), with the
 * engine's own IoStore reader and Oodle decompression.
 */
namespace RebirthDataObjectGame
{
	struct FGameFile
	{
		FString PackageName;   // /Game/DataObject/Resident/CharaSpec
		FString Container;     // full path of the .utoc without extension
		uint32 TocEntryIndex = 0;
	};

	/** The game's Paks folder: the saved choice, then the usual Steam location; asks for the game folder if bAsk. */
	FString FindPaksDirectory(bool bAsk);

	/** Every data object package in the game's containers (the base game, not ~mods), sorted by package name. */
	bool ListDataObjects(const FString& PaksDirectory, TArray<FGameFile>& OutFiles, FString& OutError);

	bool ReadPackage(const FGameFile& File, TArray<uint8>& OutBytes, FString& OutError);

	/** Reads many packages, keeping each container open between reads. */
	class FGameReader
	{
	public:
		FGameReader();
		~FGameReader();
		bool Read(const FGameFile& File, TArray<uint8>& OutBytes, FString& OutError);

	private:
		struct FImpl;
		TUniquePtr<FImpl> Impl;
	};

	/** A data object read from a game package. */
	struct FGameDataObject
	{
		UClass* Class = nullptr;
		FName ObjectName;
		RebirthDataObjectFormat::FDecoded Decoded;
		/** The game's frozen content and its name patches (offset -> name), to check a rebuilt image against. */
		TArray<uint8> Content;
		TMap<uint32, FName> NamesAt;
	};

	/** Decodes a zen (IoStore) data object package. Rows in Out.Decoded belong to the caller. */
	bool DecodePackage(const TArray<uint8>& Bytes, FGameDataObject& Out, FString& OutError);
}
