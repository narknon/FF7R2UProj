#include "RebirthDataObjectGame.h"

#include "DesktopPlatformModule.h"
#include "EndDataObjectBase.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/FileManager.h"
#include "IDesktopPlatform.h"
#include "IO/IoDispatcher.h"
#include "Logging/LogMacros.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Paths.h"
#include "UObject/Class.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectGlobals.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthGameDataObjects, Log, All);

namespace RebirthDataObjectGameDetail
{
	const TCHAR* const PaksConfigSection = TEXT("RebirthDataObjects");
	const TCHAR* const PaksConfigKey = TEXT("GamePaksDirectory");

	bool IsPaksDirectory(const FString& Directory)
	{
		TArray<FString> Found;
		IFileManager::Get().FindFiles(Found, *(Directory / TEXT("pakchunk0-*.utoc")), true, false);
		return Found.Num() > 0;
	}

	/** Accepts the game folder, End/Content or the Paks folder itself. */
	FString ResolvePaksDirectory(const FString& InDirectory)
	{
		if (InDirectory.IsEmpty())
		{
			return FString();
		}
		FString Directory = FPaths::ConvertRelativePathToFull(InDirectory);
		FPaths::NormalizeDirectoryName(Directory);
		if (IsPaksDirectory(Directory))
		{
			return Directory;
		}
		static const TCHAR* const Subfolders[] = { TEXT("End/Content/Paks"), TEXT("Content/Paks"), TEXT("Paks") };
		for (const TCHAR* Subfolder : Subfolders)
		{
			const FString Candidate = Directory / Subfolder;
			if (IsPaksDirectory(Candidate))
			{
				return Candidate;
			}
		}
		return FString();
	}

	/** Bounds-checked little-endian reads of a package. */
	struct FPackageBytes
	{
		const TArray<uint8>& Data;

		bool Has(int64 Offset, int64 Size) const
		{
			return Offset >= 0 && Size >= 0 && Offset <= Data.Num() && Size <= Data.Num() - Offset;
		}

		uint16 U16(int64 Offset) const
		{
			uint16 Value;
			FMemory::Memcpy(&Value, Data.GetData() + Offset, sizeof(Value));
			return Value;
		}

		uint32 U32(int64 Offset) const
		{
			uint32 Value;
			FMemory::Memcpy(&Value, Data.GetData() + Offset, sizeof(Value));
			return Value;
		}

		uint64 U64(int64 Offset) const
		{
			uint64 Value;
			FMemory::Memcpy(&Value, Data.GetData() + Offset, sizeof(Value));
			return Value;
		}
	};

	/** "../../../End/Content/DataObject/X.uasset" -> "/Game/DataObject/X" (empty for anything else). */
	FString DataObjectPackageName(const FString& ContainerPath)
	{
		static const FString ContentRoot = TEXT("End/Content/");
		const int32 Root = ContainerPath.Find(ContentRoot);
		if (Root == INDEX_NONE || !ContainerPath.EndsWith(TEXT(".uasset")))
		{
			return FString();
		}
		FString Relative = ContainerPath.Mid(Root + ContentRoot.Len());
		if (!Relative.StartsWith(TEXT("DataObject/")))
		{
			return FString();
		}
		Relative.LeftChopInline(7, false);
		return TEXT("/Game/") + Relative;
	}
}

namespace RebirthDataObjectGame
{
	using namespace RebirthDataObjectGameDetail;
	FString FindPaksDirectory(bool bAsk)
	{
		FString Saved;
		if (GConfig && GConfig->GetString(PaksConfigSection, PaksConfigKey, Saved, GEditorPerProjectIni))
		{
			const FString Paks = ResolvePaksDirectory(Saved);
			if (!Paks.IsEmpty())
			{
				return Paks;
			}
		}
		static const TCHAR* const Candidates[] = {
			TEXT("C:/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY VII REBIRTH"),
			TEXT("C:/Program Files/Steam/steamapps/common/FINAL FANTASY VII REBIRTH"),
			TEXT("D:/SteamLibrary/steamapps/common/FINAL FANTASY VII REBIRTH"),
			TEXT("E:/SteamLibrary/steamapps/common/FINAL FANTASY VII REBIRTH"),
			TEXT("F:/SteamLibrary/steamapps/common/FINAL FANTASY VII REBIRTH"),
		};
		for (const TCHAR* Candidate : Candidates)
		{
			const FString Paks = ResolvePaksDirectory(Candidate);
			if (!Paks.IsEmpty())
			{
				return Paks;
			}
		}
		if (bAsk && FSlateApplication::IsInitialized())
		{
			if (IDesktopPlatform* Desktop = FDesktopPlatformModule::Get())
			{
				FString Chosen;
				const void* ParentWindow = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
				if (Desktop->OpenDirectoryDialog(ParentWindow, TEXT("Select the FINAL FANTASY VII REBIRTH game folder"), FString(), Chosen))
				{
					const FString Paks = ResolvePaksDirectory(Chosen);
					if (!Paks.IsEmpty() && GConfig)
					{
						GConfig->SetString(PaksConfigSection, PaksConfigKey, *Paks, GEditorPerProjectIni);
						GConfig->Flush(false, GEditorPerProjectIni);
					}
					return Paks;
				}
			}
		}
		return FString();
	}

	bool ListDataObjects(const FString& PaksDirectory, TArray<FGameFile>& OutFiles, FString& OutError)
	{
		OutFiles.Reset();
		if (!IsPaksDirectory(PaksDirectory))
		{
			OutError = FString::Printf(TEXT("%s is not the game's Paks folder"), *PaksDirectory);
			return false;
		}
		TArray<FString> Tocs;
		IFileManager::Get().FindFiles(Tocs, *(PaksDirectory / TEXT("pakchunk*.utoc")), true, false);
		Tocs.Sort();
		TSet<FString> Seen;
		for (const FString& Toc : Tocs)
		{
			if (Toc.Contains(TEXT("optional")))
			{
				continue;
			}
			const FString Container = PaksDirectory / FPaths::GetBaseFilename(Toc);
			FIoStoreEnvironment Environment;
			Environment.InitializeFileEnvironment(Container);
			FIoStoreReader Reader;
			const FIoStatus Status = Reader.Initialize(Environment, TMap<FGuid, FAES::FAESKey>());
			if (!Status.IsOk())
			{
				UE_LOG(LogRebirthGameDataObjects, Warning, TEXT("%s could not be opened: %s"), *Toc, *Status.ToString());
				continue;
			}
			const FIoDirectoryIndexReader& Index = Reader.GetDirectoryIndexReader();
			TArray<TPair<FIoDirectoryIndexHandle, FString>> Pending;
			Pending.Emplace(FIoDirectoryIndexHandle::RootDirectory(), Index.GetMountPoint());
			while (Pending.Num() > 0)
			{
				const TPair<FIoDirectoryIndexHandle, FString> Directory = Pending.Pop(false);
				for (FIoDirectoryIndexHandle File = Index.GetFile(Directory.Key); File.IsValid(); File = Index.GetNextFile(File))
				{
					const FStringView FileName = Index.GetFileName(File);
					const FString PackageName = DataObjectPackageName(Directory.Value / FString(FileName.Len(), FileName.GetData()));
					if (PackageName.IsEmpty() || Seen.Contains(PackageName))
					{
						continue;
					}
					Seen.Add(PackageName);
					FGameFile& Entry = OutFiles.AddDefaulted_GetRef();
					Entry.PackageName = PackageName;
					Entry.Container = Container;
					Entry.TocEntryIndex = Index.GetFileData(File);
				}
				for (FIoDirectoryIndexHandle Child = Index.GetChildDirectory(Directory.Key); Child.IsValid(); Child = Index.GetNextDirectory(Child))
				{
					const FStringView ChildName = Index.GetDirectoryName(Child);
					Pending.Emplace(Child, Directory.Value / FString(ChildName.Len(), ChildName.GetData()));
				}
			}
		}
		OutFiles.Sort([](const FGameFile& A, const FGameFile& B) { return A.PackageName < B.PackageName; });
		if (OutFiles.Num() == 0)
		{
			OutError = FString::Printf(TEXT("no data objects were found in %s"), *PaksDirectory);
			return false;
		}
		return true;
	}

	bool ReadPackage(const FGameFile& File, TArray<uint8>& OutBytes, FString& OutError)
	{
		FGameReader Reader;
		return Reader.Read(File, OutBytes, OutError);
	}

	struct FGameReader::FImpl
	{
		TMap<FString, TUniquePtr<FIoStoreReader>> Readers;
	};

	FGameReader::FGameReader()
		: Impl(MakeUnique<FImpl>())
	{
	}

	FGameReader::~FGameReader() = default;

	bool FGameReader::Read(const FGameFile& File, TArray<uint8>& OutBytes, FString& OutError)
	{
		TUniquePtr<FIoStoreReader>& Cached = Impl->Readers.FindOrAdd(File.Container);
		if (!Cached.IsValid())
		{
			FIoStoreEnvironment Environment;
			Environment.InitializeFileEnvironment(File.Container);
			TUniquePtr<FIoStoreReader> Opened = MakeUnique<FIoStoreReader>();
			const FIoStatus Status = Opened->Initialize(Environment, TMap<FGuid, FAES::FAESKey>());
			if (!Status.IsOk())
			{
				Impl->Readers.Remove(File.Container);
				OutError = FString::Printf(TEXT("%s could not be opened: %s"), *File.Container, *Status.ToString());
				return false;
			}
			Cached = MoveTemp(Opened);
		}
		FIoStoreReader& Reader = *Cached;
		TIoStatusOr<FIoStoreTocChunkInfo> Info = Reader.GetChunkInfo(File.TocEntryIndex);
		if (!Info.IsOk())
		{
			OutError = FString::Printf(TEXT("%s is not in %s: %s"), *File.PackageName, *File.Container, *Info.Status().ToString());
			return false;
		}
		TIoStatusOr<FIoBuffer> Buffer = Reader.Read(Info.ValueOrDie().Id, FIoReadOptions());
		if (!Buffer.IsOk())
		{
			OutError = FString::Printf(TEXT("%s could not be read: %s"), *File.PackageName, *Buffer.Status().ToString());
			return false;
		}
		const FIoBuffer& Data = Buffer.ValueOrDie();
		OutBytes.SetNumUninitialized(int32(Data.DataSize()));
		FMemory::Memcpy(OutBytes.GetData(), Data.Data(), Data.DataSize());
		return true;
	}

	bool DecodePackage(const TArray<uint8>& Bytes, FGameDataObject& Out, FString& OutError)
	{
		const FPackageBytes Package{ Bytes };
		if (!Package.Has(0, 64))
		{
			OutError = TEXT("the package is too small");
			return false;
		}
		// 4.26 zen package summary.
		const uint32 PackageFlags = Package.U32(16);
		const uint32 CookedHeaderSize = Package.U32(20);
		const int64 NamesOffset = int32(Package.U32(24));
		const int64 NamesSize = int32(Package.U32(28));
		const int64 ExportMapOffset = int32(Package.U32(44));
		const int64 ExportBundlesOffset = int32(Package.U32(48));
		const int64 GraphOffset = int32(Package.U32(52));
		const int64 GraphSize = int32(Package.U32(56));
		if (!Package.Has(NamesOffset, NamesSize) || ExportBundlesOffset < ExportMapOffset || !Package.Has(ExportMapOffset, ExportBundlesOffset - ExportMapOffset) || !Package.Has(GraphOffset, GraphSize))
		{
			OutError = TEXT("the package header is damaged");
			return false;
		}

		TArray<FString> Names;
		for (int64 Position = NamesOffset; Position < NamesOffset + NamesSize;)
		{
			if (!Package.Has(Position, 2))
			{
				OutError = TEXT("the package name map is damaged");
				return false;
			}
			const uint8 High = Bytes[Position];
			const uint8 Low = Bytes[Position + 1];
			Position += 2;
			const bool bWide = (High & 0x80) != 0;
			const int32 Len = ((High & 0x7F) << 8) | Low;
			FString& Name = Names.AddDefaulted_GetRef();
			TArray<TCHAR>& Chars = Name.GetCharArray();
			Chars.SetNumUninitialized(Len + 1);
			if (bWide)
			{
				Position += Position & 1;
				if (!Package.Has(Position, int64(Len) * 2))
				{
					OutError = TEXT("the package name map is damaged");
					return false;
				}
				for (int32 Index = 0; Index < Len; ++Index)
				{
					Chars[Index] = static_cast<TCHAR>(Package.U16(Position + int64(Index) * 2));
				}
				Position += int64(Len) * 2;
			}
			else
			{
				if (!Package.Has(Position, Len))
				{
					OutError = TEXT("the package name map is damaged");
					return false;
				}
				for (int32 Index = 0; Index < Len; ++Index)
				{
					Chars[Index] = static_cast<TCHAR>(Bytes[Position + Index]);
				}
				Position += Len;
			}
			Chars[Len] = 0;
		}

		const int64 ExportCount = (ExportBundlesOffset - ExportMapOffset) / 72;
		if (ExportCount != 1)
		{
			OutError = FString::Printf(TEXT("the package has %lld exports; data objects have one"), ExportCount);
			return false;
		}
		const uint64 SerialOffset = Package.U64(ExportMapOffset);
		const uint64 SerialSize = Package.U64(ExportMapOffset + 8);
		const uint32 ObjectNameIndex = Package.U32(ExportMapOffset + 16) & 0x3FFFFFFFu;
		const uint32 ObjectNameNumber = Package.U32(ExportMapOffset + 20);
		const int64 HeaderEnd = GraphOffset + GraphSize;
		const int64 ExportStart = HeaderEnd + int64(SerialOffset >= CookedHeaderSize ? SerialOffset - CookedHeaderSize : SerialOffset);
		if (!Names.IsValidIndex(int32(ObjectNameIndex)) || !Package.Has(ExportStart, int64(SerialSize)))
		{
			OutError = TEXT("the package export is damaged");
			return false;
		}
		const int64 ExportEnd = ExportStart + int64(SerialSize);

		// The class: the package imports its class default object, Default__<Class>.
		FString ClassName;
		for (const FString& Name : Names)
		{
			if (Name.StartsWith(TEXT("Default__")))
			{
				ClassName = Name.Mid(9);
				break;
			}
		}
		UClass* Class = ClassName.IsEmpty() ? nullptr : FindObject<UClass>(ANY_PACKAGE, *ClassName);
		if (!Class || !Class->IsChildOf(UEndDataObjectBase::StaticClass()))
		{
			OutError = FString::Printf(TEXT("its class %s is not a data object class of this project"), ClassName.IsEmpty() ? TEXT("(unknown)") : *ClassName);
			return false;
		}
		const UEndDataObjectBase* Defaults = Class->GetDefaultObject<UEndDataObjectBase>();
		const UScriptStruct* RowStruct = Defaults ? Defaults->RowStruct : nullptr;
		if (!RowStruct)
		{
			OutError = FString::Printf(TEXT("%s has no row struct in this project"), *ClassName);
			return false;
		}

		// Properties (none in the game's data objects), the GUID flag, then the memory-mapped block.
		int64 Position = ExportStart;
		if ((PackageFlags & PKG_UnversionedProperties) != 0)
		{
			for (;;)
			{
				if (Position + 2 > ExportEnd)
				{
					OutError = TEXT("the export is damaged");
					return false;
				}
				const uint16 Fragment = Package.U16(Position);
				Position += 2;
				if ((Fragment >> 9) != 0)
				{
					OutError = TEXT("the data object has property values, which is not supported");
					return false;
				}
				if ((Fragment & 0x100) != 0)
				{
					break;
				}
			}
		}
		else
		{
			if (Position + 8 > ExportEnd || !Names.IsValidIndex(int32(Package.U32(Position))) || Names[int32(Package.U32(Position))] != TEXT("None"))
			{
				OutError = TEXT("the data object has property values, which is not supported");
				return false;
			}
			Position += 8;
		}
		if (Position + 4 > ExportEnd)
		{
			OutError = TEXT("the export is damaged");
			return false;
		}
		if (Package.U32(Position) != 0)
		{
			Position += 16;
		}
		Position += 4;
		if (Position + 12 > ExportEnd)
		{
			OutError = TEXT("the export has no memory-mapped data");
			return false;
		}
		const uint32 FrozenSize = Package.U32(Position);
		const uint16 Padding = Package.U16(Position + 10);
		Position += 12 + Padding;
		if (Position + int64(FrozenSize) + 12 > ExportEnd)
		{
			OutError = TEXT("the memory-mapped data is damaged");
			return false;
		}
		const int64 ContentStart = Position;
		Position += FrozenSize;
		const uint32 NumVTables = Package.U32(Position);
		const uint32 NumScriptNames = Package.U32(Position + 4);
		const uint32 NumNames = Package.U32(Position + 8);
		Position += 12;
		if (NumVTables != 0 || NumScriptNames != 0)
		{
			OutError = TEXT("the memory-mapped data has patches this tool does not know");
			return false;
		}
		TMap<uint32, FName> NamesAt;
		for (uint32 Entry = 0; Entry < NumNames; ++Entry)
		{
			if (Position + 12 > ExportEnd)
			{
				OutError = TEXT("the name patches are damaged");
				return false;
			}
			const uint32 NameIndex = Package.U32(Position);
			const uint32 Number = Package.U32(Position + 4);
			const uint32 Count = Package.U32(Position + 8);
			Position += 12;
			if (!Names.IsValidIndex(int32(NameIndex)) || Position + int64(Count) * 4 > ExportEnd)
			{
				OutError = TEXT("the name patches are damaged");
				return false;
			}
			const FName Name(*Names[int32(NameIndex)], int32(Number));
			for (uint32 Patch = 0; Patch < Count; ++Patch)
			{
				NamesAt.Add(Package.U32(Position + int64(Patch) * 4), Name);
			}
			Position += int64(Count) * 4;
		}

		auto NameAt = [&NamesAt](uint32 Offset) -> FName
		{
			const FName* Found = NamesAt.Find(Offset);
			return Found ? *Found : FName();
		};
		Out.Class = Class;
		Out.ObjectName = FName(*Names[int32(ObjectNameIndex)], int32(ObjectNameNumber));
		Out.Content.SetNumUninitialized(int32(FrozenSize));
		FMemory::Memcpy(Out.Content.GetData(), Bytes.GetData() + ContentStart, FrozenSize);
		Out.NamesAt = NamesAt;
		return RebirthDataObjectFormat::Decode(Bytes.GetData() + ContentStart, FrozenSize, NameAt, RowStruct, Out.Decoded, OutError);
	}
}
