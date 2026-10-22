#include "RebirthFxLinkGameAssets.h"

#include "RebirthFxLinkPaths.h"

#include "HAL/FileManager.h"
#include "IO/IoDispatcher.h"
#include "Logging/LogMacros.h"
#include "Misc/Paths.h"
#include "Serialization/AsyncLoading2.h"
#include "UObject/Package.h"
#include "UObject/PackageId.h"
#include "UObject/UObjectHash.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthFxLinkGameAssets, Log, All);

namespace RebirthFxLinkGameAssetsDetail
{
	constexpr uint64 IndexBits = 62ull;
	constexpr uint64 IndexMask = (1ull << IndexBits) - 1ull;

	uint64 TypeOf(uint64 Index)
	{
		return Index >> IndexBits;
	}

	/** Bounds-checked little-endian reads. */
	struct FBytes
	{
		const TArray<uint8>& Data;

		bool Has(int64 Offset, int64 Size) const
		{
			return Offset >= 0 && Size >= 0 && Offset <= Data.Num() && Size <= Data.Num() - Offset;
		}
		uint16 U16(int64 Offset) const { uint16 V; FMemory::Memcpy(&V, Data.GetData() + Offset, sizeof(V)); return V; }
		uint32 U32(int64 Offset) const { uint32 V; FMemory::Memcpy(&V, Data.GetData() + Offset, sizeof(V)); return V; }
		uint64 U64(int64 Offset) const { uint64 V; FMemory::Memcpy(&V, Data.GetData() + Offset, sizeof(V)); return V; }
	};

	/** A 4.26 name batch: per name a 2-byte header (bit 15 wide, 15-bit length), then the characters (wide ones 2-aligned). */
	bool ReadNameBatch(const FBytes& Bytes, int64 Offset, int64 Size, TArray<FName>& OutNames)
	{
		for (int64 Position = Offset; Position < Offset + Size;)
		{
			if (!Bytes.Has(Position, 2))
			{
				return false;
			}
			const uint8 High = Bytes.Data[Position];
			const uint8 Low = Bytes.Data[Position + 1];
			Position += 2;
			const bool bWide = (High & 0x80) != 0;
			const int32 Len = ((High & 0x7F) << 8) | Low;
			FString Name;
			TArray<TCHAR>& Chars = Name.GetCharArray();
			Chars.SetNumUninitialized(Len + 1);
			if (bWide)
			{
				Position += Position & 1;
				if (!Bytes.Has(Position, int64(Len) * 2))
				{
					return false;
				}
				for (int32 Index = 0; Index < Len; ++Index)
				{
					Chars[Index] = static_cast<TCHAR>(Bytes.U16(Position + int64(Index) * 2));
				}
				Position += int64(Len) * 2;
			}
			else
			{
				if (!Bytes.Has(Position, Len))
				{
					return false;
				}
				for (int32 Index = 0; Index < Len; ++Index)
				{
					Chars[Index] = static_cast<TCHAR>(Bytes.Data[Position + Index]);
				}
				Position += Len;
			}
			Chars[Len] = 0;
			OutNames.Add(FName(*Name));
		}
		return true;
	}

	FName MappedName(const TArray<FName>& Names, uint32 Index, uint32 Number)
	{
		const int32 NameIndex = int32(Index & 0x3FFFFFFFu);
		return Names.IsValidIndex(NameIndex) ? FName(Names[NameIndex], int32(Number)) : NAME_None;
	}

	/** "../../../End/Content/X.uasset" -> /Game/X, "../../../Engine/Content/X.uasset" -> /Engine/X. */
	FName PackageNameOfContainerPath(const FString& Path)
	{
		const bool bAsset = Path.EndsWith(TEXT(".uasset"));
		if (!bAsset && !Path.EndsWith(TEXT(".umap")))
		{
			return NAME_None;
		}
		static const FString GameRoot = TEXT("/End/Content/");
		static const FString EngineRoot = TEXT("/Engine/Content/");
		FString Relative;
		FString Root;
		int32 Found = Path.Find(GameRoot);
		if (Found != INDEX_NONE)
		{
			Relative = Path.Mid(Found + GameRoot.Len());
			Root = TEXT("/Game/");
		}
		else if ((Found = Path.Find(EngineRoot)) != INDEX_NONE)
		{
			Relative = Path.Mid(Found + EngineRoot.Len());
			Root = TEXT("/Engine/");
		}
		else
		{
			return NAME_None;
		}
		Relative.LeftChopInline(bAsset ? 7 : 5, false);
		return FName(*(Root + Relative));
	}

	/** Script objects in memory by the import hash the game's packages use for them. */
	TMap<uint64, TWeakObjectPtr<UObject>> GScriptObjects;
	int32 GScriptObjectCount = 0;

	void AddScriptObjects(UObject* Outer)
	{
		TArray<UObject*> Inner;
		GetObjectsWithOuter(Outer, Inner, false);
		for (UObject* Object : Inner)
		{
			if (!Object->HasAnyFlags(RF_Public))
			{
				continue;
			}
			GScriptObjects.Add(FPackageObjectIndex::FromScriptPath(Object->GetPathName()).Value(), Object);
			AddScriptObjects(Object);
		}
	}

	void BuildScriptObjects()
	{
		int32 Count = 0;
		for (TObjectIterator<UPackage> It; It; ++It)
		{
			if (It->HasAnyPackageFlags(PKG_CompiledIn) && It->GetOuter() == nullptr)
			{
				++Count;
			}
		}
		if (Count == GScriptObjectCount && GScriptObjects.Num() > 0)
		{
			return;
		}
		GScriptObjects.Reset();
		GScriptObjectCount = Count;
		for (TObjectIterator<UPackage> It; It; ++It)
		{
			UPackage* Package = *It;
			if (Package->HasAnyPackageFlags(PKG_CompiledIn) && Package->GetOuter() == nullptr)
			{
				GScriptObjects.Add(FPackageObjectIndex::FromScriptPath(Package->GetName()).Value(), Package);
				AddScriptObjects(Package);
			}
		}
	}
}

namespace RebirthFxLinkGameAssets
{
	using namespace RebirthFxLinkGameAssetsDetail;

	bool IsNullIndex(uint64 Index) { return Index == ~0ull; }
	bool IsExportIndex(uint64 Index) { return !IsNullIndex(Index) && TypeOf(Index) == 0; }
	bool IsScriptImport(uint64 Index) { return !IsNullIndex(Index) && TypeOf(Index) == 1; }
	bool IsPackageImport(uint64 Index) { return !IsNullIndex(Index) && TypeOf(Index) == 2; }
	int32 ExportIndexOf(uint64 Index) { return IsExportIndex(Index) ? int32(Index & IndexMask) : INDEX_NONE; }

	bool ParseZenPackage(const TArray<uint8>& Data, FZenPackage& Out, FString& OutError)
	{
		const FBytes Bytes{ Data };
		if (!Bytes.Has(0, 64))
		{
			OutError = TEXT("the package is too small");
			return false;
		}
		const uint32 NameIndex = Bytes.U32(0);
		const uint32 NameNumber = Bytes.U32(4);
		Out.PackageFlags = Bytes.U32(16);
		Out.CookedHeaderSize = Bytes.U32(20);
		const int64 NamesOffset = int32(Bytes.U32(24));
		const int64 NamesSize = int32(Bytes.U32(28));
		const int64 ImportMapOffset = int32(Bytes.U32(40));
		const int64 ExportMapOffset = int32(Bytes.U32(44));
		const int64 ExportBundlesOffset = int32(Bytes.U32(48));
		const int64 GraphOffset = int32(Bytes.U32(52));
		const int64 GraphSize = int32(Bytes.U32(56));
		if (!Bytes.Has(NamesOffset, NamesSize) || ImportMapOffset > ExportMapOffset || ExportMapOffset > ExportBundlesOffset
			|| ExportBundlesOffset > GraphOffset || !Bytes.Has(GraphOffset, GraphSize) || !Bytes.Has(ImportMapOffset, ExportMapOffset - ImportMapOffset))
		{
			OutError = TEXT("the package header is damaged");
			return false;
		}
		Out.Names.Reset();
		if (!ReadNameBatch(Bytes, NamesOffset, NamesSize, Out.Names))
		{
			OutError = TEXT("the package name map is damaged");
			return false;
		}
		Out.PackageName = MappedName(Out.Names, NameIndex, NameNumber);
		Out.HeaderSize = GraphOffset + GraphSize;

		Out.Imports.Reset();
		for (int64 Position = ImportMapOffset; Position + 8 <= ExportMapOffset; Position += 8)
		{
			Out.Imports.Add(Bytes.U64(Position));
		}

		const int64 ExportCount = (ExportBundlesOffset - ExportMapOffset) / 72;
		Out.Exports.Reset();
		for (int64 Index = 0; Index < ExportCount; ++Index)
		{
			const int64 Entry = ExportMapOffset + Index * 72;
			FZenExport& Export = Out.Exports.AddDefaulted_GetRef();
			Export.CookedSerialOffset = Bytes.U64(Entry);
			Export.CookedSerialSize = Bytes.U64(Entry + 8);
			Export.ObjectName = MappedName(Out.Names, Bytes.U32(Entry + 16), Bytes.U32(Entry + 20));
			Export.OuterIndex = Bytes.U64(Entry + 24);
			Export.ClassIndex = Bytes.U64(Entry + 32);
			Export.SuperIndex = Bytes.U64(Entry + 40);
			Export.TemplateIndex = Bytes.U64(Entry + 48);
			Export.GlobalImportIndex = Bytes.U64(Entry + 56);
			Export.ObjectFlags = Bytes.U32(Entry + 64);
			Export.FilterFlags = Data[Entry + 68];
		}

		// Export bundles: every bundle header (first entry, entry count), then every entry (export, command).
		Out.BundleEntries.Reset();
		const int64 BundleSectionWords = (GraphOffset - ExportBundlesOffset) / 8;
		int64 Headers = 0;
		int64 Entries = 0;
		while (Headers + Entries < BundleSectionWords)
		{
			Entries += Bytes.U32(ExportBundlesOffset + Headers * 8 + 4);
			++Headers;
		}
		if (Headers + Entries != BundleSectionWords)
		{
			OutError = TEXT("the package export bundles are damaged");
			return false;
		}
		for (int64 Entry = 0; Entry < Entries; ++Entry)
		{
			const int64 Position = ExportBundlesOffset + (Headers + Entry) * 8;
			Out.BundleEntries.Emplace(Bytes.U32(Position), Bytes.U32(Position + 4));
		}

		// Export data follows the header in the order of the bundles' serialize commands.
		int64 DataPosition = Out.HeaderSize;
		for (const TPair<uint32, uint32>& Entry : Out.BundleEntries)
		{
			if (Entry.Value == 1 && Out.Exports.IsValidIndex(int32(Entry.Key)))
			{
				FZenExport& Export = Out.Exports[int32(Entry.Key)];
				Export.DataOffset = DataPosition;
				DataPosition += int64(Export.CookedSerialSize);
			}
		}

		// Graph: imported packages (id, arc count, arcs).
		Out.ImportedPackageIds.Reset();
		if (GraphSize >= 4)
		{
			const int32 Count = int32(Bytes.U32(GraphOffset));
			int64 Position = GraphOffset + 4;
			for (int32 Index = 0; Index < Count && Position + 12 <= GraphOffset + GraphSize; ++Index)
			{
				Out.ImportedPackageIds.Add(Bytes.U64(Position));
				const int32 Arcs = int32(Bytes.U32(Position + 8));
				Position += 12 + int64(Arcs) * 8;
			}
		}
		return true;
	}

	FString GetExportPath(const FZenPackage& Package, int32 ExportIndex)
	{
		TArray<FName> Chain;
		int32 Current = ExportIndex;
		while (Package.Exports.IsValidIndex(Current) && Chain.Num() < 64)
		{
			Chain.Insert(Package.Exports[Current].ObjectName, 0);
			Current = ExportIndexOf(Package.Exports[Current].OuterIndex);
		}
		FString Path = Package.PackageName.ToString();
		for (int32 Index = 0; Index < Chain.Num(); ++Index)
		{
			Path += Index == 0 ? TEXT(".") : (Index == 1 ? TEXT(":") : TEXT("."));
			Path += Chain[Index].ToString();
		}
		return Path;
	}

	UObject* FindScriptObject(uint64 ScriptImportIndex)
	{
		if (!IsScriptImport(ScriptImportIndex))
		{
			return nullptr;
		}
		BuildScriptObjects();
		const TWeakObjectPtr<UObject>* Found = GScriptObjects.Find(ScriptImportIndex & IndexMask);
		return Found ? Found->Get() : nullptr;
	}

	struct FGameIndex::FImpl
	{
		TArray<FString> Containers;
		TMap<int32, TUniquePtr<FIoStoreReader>> Readers;
	};

	FGameIndex& FGameIndex::Get()
	{
		static FGameIndex Index;
		return Index;
	}

	FGameIndex::FGameIndex()
		: Impl(MakeUnique<FImpl>())
	{
	}

	FGameIndex::~FGameIndex() = default;

	bool FGameIndex::Initialize(FString& OutError)
	{
		if (bInitialized)
		{
			return true;
		}
		if (!InitializeError.IsEmpty())
		{
			OutError = InitializeError;
			return false;
		}
		const double Start = FPlatformTime::Seconds();
		const FString Paks = RebirthFxLinkPaths::FindPaksDirectory(false);
		if (Paks.IsEmpty())
		{
			InitializeError = TEXT("the game's Paks folder was not found");
			OutError = InitializeError;
			return false;
		}
		TArray<FString> Tocs;
		IFileManager::Get().FindFiles(Tocs, *(Paks / TEXT("pakchunk*.utoc")), true, false);
		Tocs.Sort();
		for (const FString& Toc : Tocs)
		{
			if (Toc.Contains(TEXT("optional")))
			{
				continue;
			}
			const FString Container = Paks / FPaths::GetBaseFilename(Toc);
			FIoStoreEnvironment Environment;
			Environment.InitializeFileEnvironment(Container);
			TUniquePtr<FIoStoreReader> Reader = MakeUnique<FIoStoreReader>();
			const FIoStatus Status = Reader->Initialize(Environment, TMap<FGuid, FAES::FAESKey>());
			if (!Status.IsOk())
			{
				UE_LOG(LogRebirthFxLinkGameAssets, Warning, TEXT("%s could not be opened: %s"), *Toc, *Status.ToString());
				continue;
			}
			const int32 ContainerIndex = Impl->Containers.Add(Container);
			const FIoDirectoryIndexReader& Index = Reader->GetDirectoryIndexReader();
			TArray<TPair<FIoDirectoryIndexHandle, FString>> Pending;
			Pending.Emplace(FIoDirectoryIndexHandle::RootDirectory(), Index.GetMountPoint());
			while (Pending.Num() > 0)
			{
				const TPair<FIoDirectoryIndexHandle, FString> Directory = Pending.Pop(false);
				for (FIoDirectoryIndexHandle File = Index.GetFile(Directory.Key); File.IsValid(); File = Index.GetNextFile(File))
				{
					const FStringView FileName = Index.GetFileName(File);
					const FName PackageName = PackageNameOfContainerPath(Directory.Value / FString(FileName.Len(), FileName.GetData()));
					if (PackageName.IsNone() || Packages.Contains(PackageName))
					{
						continue;
					}
					FEntry& Entry = Packages.Add(PackageName);
					Entry.Container = ContainerIndex;
					Entry.TocEntryIndex = Index.GetFileData(File);
				}
				for (FIoDirectoryIndexHandle Child = Index.GetChildDirectory(Directory.Key); Child.IsValid(); Child = Index.GetNextDirectory(Child))
				{
					const FStringView ChildName = Index.GetDirectoryName(Child);
					Pending.Emplace(Child, Directory.Value / FString(ChildName.Len(), ChildName.GetData()));
				}
			}
			Impl->Readers.Add(ContainerIndex, MoveTemp(Reader));
		}
		if (Packages.Num() == 0)
		{
			InitializeError = FString::Printf(TEXT("no packages were found in %s"), *Paks);
			OutError = InitializeError;
			return false;
		}
		bInitialized = true;
		UE_LOG(LogRebirthFxLinkGameAssets, Display, TEXT("Game package index: %d packages in %d containers (%.1f s)."), Packages.Num(), Impl->Containers.Num(), FPlatformTime::Seconds() - Start);
		return true;
	}

	bool FGameIndex::Contains(FName PackageName) const
	{
		return Packages.Contains(PackageName);
	}

	int32 FGameIndex::Num() const
	{
		return Packages.Num();
	}

	bool FGameIndex::ReadPackage(FName PackageName, TArray<uint8>& OutBytes, FString& OutError)
	{
		if (!Initialize(OutError))
		{
			return false;
		}
		const FEntry* Entry = Packages.Find(PackageName);
		if (!Entry)
		{
			OutError = FString::Printf(TEXT("%s is not in the game"), *PackageName.ToString());
			return false;
		}
		TUniquePtr<FIoStoreReader>* Reader = Impl->Readers.Find(Entry->Container);
		if (!Reader || !Reader->IsValid())
		{
			OutError = TEXT("the game container is not open");
			return false;
		}
		TIoStatusOr<FIoStoreTocChunkInfo> Info = (*Reader)->GetChunkInfo(Entry->TocEntryIndex);
		if (!Info.IsOk())
		{
			OutError = FString::Printf(TEXT("%s: %s"), *PackageName.ToString(), *Info.Status().ToString());
			return false;
		}
		TIoStatusOr<FIoBuffer> Buffer = (*Reader)->Read(Info.ValueOrDie().Id, FIoReadOptions());
		if (!Buffer.IsOk())
		{
			OutError = FString::Printf(TEXT("%s could not be read: %s"), *PackageName.ToString(), *Buffer.Status().ToString());
			return false;
		}
		const FIoBuffer& Data = Buffer.ValueOrDie();
		OutBytes.SetNumUninitialized(int32(Data.DataSize()));
		FMemory::Memcpy(OutBytes.GetData(), Data.Data(), Data.DataSize());
		return true;
	}

	bool FGameIndex::ReadContainerHeaderFor(FName PackageName, TArray<uint8>& OutBytes, FString& OutContainer, FString& OutError)
	{
		if (!Initialize(OutError))
		{
			return false;
		}
		const FEntry* Entry = Packages.Find(PackageName);
		if (!Entry)
		{
			OutError = FString::Printf(TEXT("%s is not in the game"), *PackageName.ToString());
			return false;
		}
		TUniquePtr<FIoStoreReader>* Reader = Impl->Readers.Find(Entry->Container);
		if (!Reader || !Reader->IsValid())
		{
			OutError = TEXT("the game container is not open");
			return false;
		}
		const FIoChunkId HeaderId = CreateIoChunkId((*Reader)->GetContainerId().Value(), 0, EIoChunkType::ContainerHeader);
		TIoStatusOr<FIoBuffer> Buffer = (*Reader)->Read(HeaderId, FIoReadOptions());
		if (!Buffer.IsOk())
		{
			OutError = FString::Printf(TEXT("the container header of %s could not be read: %s"), *PackageName.ToString(), *Buffer.Status().ToString());
			return false;
		}
		const FIoBuffer& Data = Buffer.ValueOrDie();
		OutBytes.SetNumUninitialized(int32(Data.DataSize()));
		FMemory::Memcpy(OutBytes.GetData(), Data.Data(), Data.DataSize());
		OutContainer = Impl->Containers.IsValidIndex(Entry->Container) ? FPaths::GetBaseFilename(Impl->Containers[Entry->Container]) : FString();
		return true;
	}

	bool FGameIndex::ReadZenPackage(FName PackageName, FZenPackage& Out, FString& OutError)
	{
		TArray<uint8> Bytes;
		return ReadPackage(PackageName, Bytes, OutError) && ParseZenPackage(Bytes, Out, OutError);
	}

	FName FGameIndex::FindPackageById(uint64 PackageId)
	{
		FString Error;
		if (!Initialize(Error))
		{
			return NAME_None;
		}
		if (PackagesById.Num() == 0)
		{
			PackagesById.Reserve(Packages.Num());
			for (const TPair<FName, FEntry>& Package : Packages)
			{
				PackagesById.Add(FPackageId::FromName(Package.Key).ValueForDebugging(), Package.Key);
			}
		}
		const FName* Found = PackagesById.Find(PackageId);
		return Found ? *Found : NAME_None;
	}

	bool FGameIndex::ResolvePackageImport(const FZenPackage& Package, uint64 PackageImportIndex, FName& OutPackageName, FString& OutObjectPath, int32& OutExportIndex)
	{
		if (!IsPackageImport(PackageImportIndex))
		{
			return false;
		}
		for (const uint64 Id : Package.ImportedPackageIds)
		{
			const FName Imported = FindPackageById(Id);
			FZenPackage ImportedPackage;
			FString Error;
			if (Imported.IsNone() || !ReadZenPackage(Imported, ImportedPackage, Error))
			{
				continue;
			}
			for (int32 Index = 0; Index < ImportedPackage.Exports.Num(); ++Index)
			{
				if (ImportedPackage.Exports[Index].GlobalImportIndex == PackageImportIndex)
				{
					OutPackageName = Imported;
					OutObjectPath = GetExportPath(ImportedPackage, Index);
					OutExportIndex = Index;
					return true;
				}
			}
		}
		return false;
	}

	void FGameIndex::GetPackageNames(TArray<FName>& OutNames) const
	{
		Packages.GenerateKeyArray(OutNames);
		OutNames.Sort(FNameLexicalLess());
	}
}
