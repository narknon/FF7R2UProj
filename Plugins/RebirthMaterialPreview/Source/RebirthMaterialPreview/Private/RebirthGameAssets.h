#pragma once

#include "CoreMinimal.h"

class UObject;

/**
 * Read access to the game's own packages (End/Content/Paks/pakchunk*.utoc/.ucas, IoStore "zen" format), for things
 * this project only knows by reference: the class and super class of a game blueprint that is not in the project,
 * the exports of a game package, and so on. The index is built once per process from the containers' directory
 * indexes (no dialogs; the Paks folder comes from RebirthDataObjectGame::FindPaksDirectory).
 */
namespace RebirthGameAssets
{
	/** One export of a zen package. The indices are raw FPackageObjectIndex values (see IsScriptImport etc.). */
	struct FZenExport
	{
		FName ObjectName;
		uint64 OuterIndex = ~0ull;
		uint64 ClassIndex = ~0ull;
		uint64 SuperIndex = ~0ull;
		uint64 TemplateIndex = ~0ull;
		uint64 GlobalImportIndex = ~0ull;
		uint32 ObjectFlags = 0;
		uint8 FilterFlags = 0;
		uint64 CookedSerialOffset = 0;
		uint64 CookedSerialSize = 0;
		/** Where the export's serialized data starts in the package chunk. */
		int64 DataOffset = -1;
	};

	struct FZenPackage
	{
		FName PackageName;
		uint32 PackageFlags = 0;
		uint32 CookedHeaderSize = 0;
		int64 HeaderSize = 0;
		TArray<FName> Names;
		TArray<uint64> Imports;
		TArray<FZenExport> Exports;
		/** (export index, 0 = create / 1 = serialize) in load order. */
		TArray<TPair<uint32, uint32>> BundleEntries;
		TArray<uint64> ImportedPackageIds;
	};

	bool IsNullIndex(uint64 Index);
	bool IsExportIndex(uint64 Index);
	bool IsScriptImport(uint64 Index);
	bool IsPackageImport(uint64 Index);
	int32 ExportIndexOf(uint64 Index);

	bool ParseZenPackage(const TArray<uint8>& Bytes, FZenPackage& Out, FString& OutError);

	/** "Package.Name" or "Package.Outer:Name" for an export. */
	FString GetExportPath(const FZenPackage& Package, int32 ExportIndex);

	/** The in-memory /Script object a zen script import refers to (nullptr if this project has no such object). */
	UObject* FindScriptObject(uint64 ScriptImportIndex);

	class FGameIndex
	{
	public:
		static FGameIndex& Get();

		/** Builds the index on first use. False (with a reason) when the game's Paks folder is unknown or unreadable. */
		bool Initialize(FString& OutError);
		bool IsInitialized() const { return bInitialized; }

		/** True for a package that exists in the game (e.g. /Game/Motion/Player/PC0011_Vincent/Battle00). */
		bool Contains(FName PackageName) const;
		int32 Num() const;

		bool ReadPackage(FName PackageName, TArray<uint8>& OutBytes, FString& OutError);
		bool ReadZenPackage(FName PackageName, FZenPackage& Out, FString& OutError);

		/** The container header (package store entries) of the game container holding PackageName, and its name. */
		bool ReadContainerHeaderFor(FName PackageName, TArray<uint8>& OutBytes, FString& OutContainer, FString& OutError);

		/** The game package with this FPackageId value (builds the id table on first use). */
		FName FindPackageById(uint64 PackageId);

		/** Object path of a package import (FPackageObjectIndex) of Package: found among the packages it imports. */
		bool ResolvePackageImport(const FZenPackage& Package, uint64 PackageImportIndex, FName& OutPackageName, FString& OutObjectPath, int32& OutExportIndex);

		/** Every game package name (sorted). */
		void GetPackageNames(TArray<FName>& OutNames) const;

	private:
		struct FEntry
		{
			int32 Container = INDEX_NONE;
			uint32 TocEntryIndex = 0;
		};
		struct FImpl;

		FGameIndex();
		~FGameIndex();

		bool bInitialized = false;
		FString InitializeError;
		TMap<FName, FEntry> Packages;
		TMap<uint64, FName> PackagesById;
		TUniquePtr<FImpl> Impl;
	};
}
