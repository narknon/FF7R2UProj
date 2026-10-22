#include "RebirthDataObjectSerialization.h"

#include "RebirthCharaSpecCheck.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Editor.h"
#include "EndDataObjectBase.h"
#include "EndDataObjectSerializeHandler.h"
#include "GameDelegates.h"
#include "Logging/LogMacros.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Modules/ModuleManager.h"
#include "Serialization/Archive.h"
#include "Settings/ProjectPackagingSettings.h"
#include "UObject/Class.h"
#include "UObject/Linker.h"
#include "UObject/LinkerLoad.h"
#include "UObject/NameTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectIterator.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthDataObjects, Log, All);

namespace RebirthDataObjectsDetail
{
	using namespace RebirthDataObjectFormat;

	/** Editor saves: "RRDO", version, row struct path, row count, then (row name, tagged row) per row. */
	constexpr uint32 EditorBlockMagic = 0x4F445252;
	constexpr uint32 EditorBlockVersion = 1;

	/** Constant header fields of the game's memory-mapped data objects. */
	constexpr uint32 FrozenHeaderField = 0x10000;
	constexpr uint16 FrozenAlignmentField = 16;

	bool GDataObjectsInstalled = false;
	FEndDataObjectSerializeHandler GPreviousSerializeHandler = nullptr;
	FCookModificationDelegate GPreviousCookModification;
	bool GCookModificationBound = false;
	TSet<FString> GReportedCookErrors;
	TSet<FString> GCheckedForCook;

	bool IsMemoryMappedPackage(const UEndDataObjectBase& Object)
	{
		const UPackage* Package = Object.GetOutermost();
		return Package && Package->HasAnyPackageFlags(PKG_MemoryMappedAsset);
	}

	int64 GetExportEnd(const UObject& Object)
	{
		FLinkerLoad* Linker = Object.GetLinker();
		const int32 Index = Object.GetLinkerIndex();
		if (Linker && Linker->ExportMap.IsValidIndex(Index))
		{
			const FObjectExport& Export = Linker->ExportMap[Index];
			return Export.SerialOffset + Export.SerialSize;
		}
		return INDEX_NONE;
	}

	void WriteZeros(FArchive& Ar, int32 Count)
	{
		uint8 Zeros[16] = {};
		while (Count > 0)
		{
			const int32 Chunk = FMath::Min(Count, 16);
			Ar.Serialize(Zeros, Chunk);
			Count -= Chunk;
		}
	}

	/** A cooked data object: properties, then the game's frozen content with the names already patched in. */
	void LoadCooked(UEndDataObjectBase& Object, FArchive& Ar)
	{
		Object.UMemoryMappedAsset::Serialize(Ar);
		uint8* Content = Object.Content;
		const uint32 ContentSize = Object.FrozenContentSize;
		Object.Content = nullptr;
		if (Content && ContentSize > 0)
		{
			if (Object.RowStruct)
			{
				auto NameAt = [Content, ContentSize](uint32 Offset) -> FName
				{
					if (uint64(Offset) + sizeof(FMinimalName) > uint64(ContentSize))
					{
						return NAME_None;
					}
					FMinimalName Minimal;
					FMemory::Memcpy(&Minimal, Content + Offset, sizeof(Minimal));
					return MinimalNameToName(Minimal);
				};
				FDecoded Decoded;
				FString Error;
				if (Decode(Content, ContentSize, NameAt, Object.RowStruct, Decoded, Error))
				{
					RebirthDataObjects::AssignDecoded(Object, Decoded);
				}
				else
				{
					UE_LOG(LogRebirthDataObjects, Error, TEXT("%s: the game's data could not be read: %s"), *Object.GetPathName(), *Error);
				}
			}
			FMemory::Free(Content);
		}
		// The game's files pad each data object to a multiple of 16 bytes after the name patches.
		const int64 End = GetExportEnd(Object);
		const int64 Position = Ar.Tell();
		if (End > Position && End - Position < 16)
		{
			Ar.Seek(End);
		}
	}

	/** Cooking: properties, then the rows in the game's memory-mapped format. */
	void SaveCooked(UEndDataObjectBase& Object, FArchive& Ar)
	{
		const int64 ExportStart = Ar.Tell();
		// Writes the (non editor-only) properties and flags the package as memory-mapped for the game's loader.
		Object.UMemoryMappedAsset::Serialize(Ar);

		// CharaSpec rows that refer to things the game can't find hang its loading screen: say so in the cook log.
		if (RebirthCharaSpecCheck::IsCharaSpecTable(Object) && !GCheckedForCook.Contains(Object.GetPathName()))
		{
			GCheckedForCook.Add(Object.GetPathName());
			RebirthCharaSpecCheck::CheckAndReport(Object, false);
		}

		FImage Image;
		FString Error;
		if (!RebirthDataObjects::BuildImage(Object, Image, Error))
		{
			const FString Path = Object.GetPathName();
			if (!GReportedCookErrors.Contains(Path))
			{
				GReportedCookErrors.Add(Path);
				UE_LOG(LogRebirthDataObjects, Error, TEXT("%s cannot be cooked in the game's format: %s. It is cooked without rows."), *Path, *Error);
			}
			FString Ignored;
			Encode(FLayout(), TArray<FName>(), TArray<const uint8*>(), Image, Ignored);
		}

		uint32 FrozenSize = uint32(Image.Content.Num());
		uint32 HeaderField = FrozenHeaderField;
		uint16 AlignmentField = FrozenAlignmentField;
		// The content starts on a 16-byte boundary of the export, as in the game's files.
		const int64 ContentStart = Ar.Tell() + 12 - ExportStart;
		uint16 Padding = uint16((16 - (ContentStart & 15)) & 15);
		Ar << FrozenSize;
		Ar << HeaderField;
		Ar << AlignmentField;
		Ar << Padding;
		WriteZeros(Ar, Padding);
		Ar.Serialize(Image.Content.GetData(), FrozenSize);

		uint32 NumVTables = 0;
		uint32 NumScriptNames = 0;
		uint32 NumNames = uint32(Image.Names.Num());
		Ar << NumVTables;
		Ar << NumScriptNames;
		Ar << NumNames;
		for (TPair<FName, TArray<uint32>>& Entry : Image.Names)
		{
			FName Name = Entry.Key;
			uint32 NumOffsets = uint32(Entry.Value.Num());
			Ar << Name;
			Ar << NumOffsets;
			for (uint32& Offset : Entry.Value)
			{
				Ar << Offset;
			}
		}
		// The export ends on a 16-byte boundary, as in the game's files.
		const int64 Size = Ar.Tell() - ExportStart;
		WriteZeros(Ar, int32((16 - (Size & 15)) & 15));
	}

	/** Editor assets and undo: properties (with the game's row layout), then every row as tagged properties. */
	void SaveEditor(UEndDataObjectBase& Object, FArchive& Ar)
	{
		if (Ar.GetLinker() != nullptr && !Ar.IsTransacting())
		{
			// Editable packages are not memory-mapped (the flag can be left over from a cooked copy).
			Object.GetOutermost()->ClearPackageFlags(PKG_MemoryMappedAsset);
		}
		Object.UObject::Serialize(Ar);

		uint32 Magic = EditorBlockMagic;
		uint32 Version = EditorBlockVersion;
		FString StructPath = Object.RowStruct ? Object.RowStruct->GetPathName() : FString();
		int32 NumRows = Object.RowStruct ? Object.RowMap.Num() : 0;
		Ar << Magic;
		Ar << Version;
		Ar << StructPath;
		Ar << NumRows;
		if (NumRows > 0)
		{
			for (TPair<FName, uint8*>& Row : Object.RowMap)
			{
				FName RowName = Row.Key;
				Ar << RowName;
				Object.RowStruct->SerializeItem(Ar, Row.Value, nullptr);
			}
		}
	}

	void LoadEditor(UEndDataObjectBase& Object, FArchive& Ar)
	{
		Object.UObject::Serialize(Ar);
		const int64 End = GetExportEnd(Object);
		const int64 Start = Ar.Tell();
		if (End != INDEX_NONE && End - Start < 16)
		{
			// Saved before rows were kept with the asset.
			return;
		}
		uint32 Magic = 0;
		Ar << Magic;
		if (Magic != EditorBlockMagic)
		{
			Ar.Seek(Start);
			return;
		}
		uint32 Version = 0;
		FString StructPath;
		int32 NumRows = 0;
		Ar << Version;
		Ar << StructPath;
		Ar << NumRows;
		if (Version != EditorBlockVersion || NumRows < 0 || (NumRows > 0 && !Object.RowStruct))
		{
			UE_LOG(LogRebirthDataObjects, Error, TEXT("%s: the saved rows cannot be read (version %u, %d rows, row struct %s)."),
				*Object.GetPathName(), Version, NumRows, *StructPath);
			if (End != INDEX_NONE)
			{
				Ar.Seek(End);
			}
			return;
		}
		if (NumRows > 0 && StructPath != Object.RowStruct->GetPathName())
		{
			UE_LOG(LogRebirthDataObjects, Warning, TEXT("%s: rows were saved as %s and are read as %s (matching fields by name)."),
				*Object.GetPathName(), *StructPath, *Object.RowStruct->GetPathName());
		}
		Object.EmptyTable();
		Object.RowMap.Reserve(NumRows);
		for (int32 Index = 0; Index < NumRows && !Ar.IsError(); ++Index)
		{
			FName RowName;
			Ar << RowName;
			uint8* Row = static_cast<uint8*>(FMemory::Malloc(Object.RowStruct->GetStructureSize()));
			Object.RowStruct->InitializeStruct(Row);
			Object.RowStruct->SerializeItem(Ar, Row, nullptr);
			if (uint8** Existing = Object.RowMap.Find(RowName))
			{
				Object.RowStruct->DestroyStruct(*Existing);
				FMemory::Free(*Existing);
				*Existing = Row;
			}
			else
			{
				Object.RowMap.Add(RowName, Row);
			}
		}
	}

	bool HandleSerialize(UEndDataObjectBase& Object, FArchive& Ar)
	{
		if (Object.HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
		{
			return GPreviousSerializeHandler != nullptr && GPreviousSerializeHandler(Object, Ar);
		}
		if (Ar.IsLoading())
		{
			if (!Ar.IsTransacting() && IsMemoryMappedPackage(Object))
			{
				LoadCooked(Object, Ar);
			}
			else
			{
				LoadEditor(Object, Ar);
			}
			return true;
		}
		if (Ar.IsSaving())
		{
			if (Ar.IsCooking())
			{
				SaveCooked(Object, Ar);
			}
			else
			{
				SaveEditor(Object, Ar);
			}
			return true;
		}
		// Reference collection, counting and similar passes: rows hold no object references.
		Object.UObject::Serialize(Ar);
		return true;
	}

	/**
	 * UCookOnTheFlyServer::CollectFilesToCook cooks every package of the project when nothing names what to cook (no
	 * maps in the settings or on the command line, no directories to always cook, nothing added by this delegate).
	 * Adding packages here would turn that off and leave the rest of the project out of the cook.
	 */
	bool CookAddsEverything()
	{
		const UProjectPackagingSettings* Settings = GetDefault<UProjectPackagingSettings>();
		const TCHAR* CommandLine = FCommandLine::Get();
		if (Settings->bCookAll || FParse::Param(CommandLine, TEXT("CookAll")))
		{
			return true;
		}
		FString Value;
		if (Settings->MapsToCook.Num() > 0 || Settings->DirectoriesToAlwaysCook.Num() > 0 || FParse::Value(CommandLine, TEXT("-Map="), Value)
			|| FParse::Value(CommandLine, TEXT("-CookDir="), Value) || FParse::Value(CommandLine, TEXT("-MapIniSection="), Value)
			|| FParse::Value(CommandLine, TEXT("-DLCName="), Value))
		{
			return false;
		}
		if (GEditor)
		{
			TArray<FString> Maps;
			GEditor->LoadMapListFromIni(TEXT("AlwaysCookMaps"), Maps);
			GEditor->LoadMapListFromIni(TEXT("AllMaps"), Maps);
			return Maps.Num() == 0;
		}
		return false;
	}

	/** When the cook only takes what maps reference, edited data objects under /Game are added explicitly. */
	void AppendDataObjectsToCook(TArray<FString>& PackagesToCook)
	{
		if (CookAddsEverything())
		{
			UE_LOG(LogRebirthDataObjects, Display, TEXT("This cook takes every package in the project, edited data objects included."));
			return;
		}
		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
		if (Registry.IsLoadingAssets())
		{
			Registry.SearchAllAssets(true);
		}
		TArray<FAssetData> Assets;
		Registry.GetAssetsByClass(UEndDataObjectBase::StaticClass()->GetFName(), Assets, true);
		Assets.Sort([](const FAssetData& A, const FAssetData& B) { return A.PackageName.LexicalLess(B.PackageName); });
		for (const FAssetData& Asset : Assets)
		{
			if ((Asset.PackageFlags & (PKG_Cooked | PKG_FilterEditorOnly)) != 0)
			{
				continue;
			}
			const FString PackageName = Asset.PackageName.ToString();
			if (!PackageName.StartsWith(TEXT("/Game/")) || PackageName.StartsWith(TEXT("/Game/RebirthDataObjectTests/")) || PackagesToCook.Contains(PackageName))
			{
				continue;
			}
			UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(Asset.GetAsset());
			if (!DataObject)
			{
				continue;
			}
			if (!RebirthDataObjects::HasGameLayout(*DataObject))
			{
				UE_LOG(LogRebirthDataObjects, Display, TEXT("%s is not added to the cook: its game row layout is unknown (import it from the game first)."), *PackageName);
				continue;
			}
			PackagesToCook.Add(PackageName);
			UE_LOG(LogRebirthDataObjects, Display, TEXT("Cooking edited data object %s (%d rows) in the game's format."), *PackageName, DataObject->RowMap.Num());
		}
	}

	void OnCookModification(TArray<FString>& PackagesToCook)
	{
		AppendDataObjectsToCook(PackagesToCook);
		// Runs last: the cooked-texture skip swaps the asset manager for the ModifyCook call that follows this delegate.
		GPreviousCookModification.ExecuteIfBound(PackagesToCook);
	}
}

namespace RebirthDataObjects
{
	using namespace RebirthDataObjectsDetail;
	using namespace RebirthDataObjectFormat;

	void Install()
	{
		if (GDataObjectsInstalled)
		{
			return;
		}
		GPreviousSerializeHandler = GEndDataObjectSerializeHandler;
		GEndDataObjectSerializeHandler = &HandleSerialize;
		if (IsRunningCommandlet())
		{
			FCookModificationDelegate& Delegate = FGameDelegates::Get().GetCookModificationDelegate();
			GPreviousCookModification = Delegate;
			Delegate.BindStatic(&OnCookModification);
			GCookModificationBound = true;
		}
		GDataObjectsInstalled = true;

		for (TObjectIterator<UEndDataObjectBase> It; It; ++It)
		{
			if (!It->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject) && It->RowMap.Num() > 0 && !HasGameLayout(**It))
			{
				UE_LOG(LogRebirthDataObjects, Warning, TEXT("%s was loaded before data object support started; reload it before editing or cooking."), *It->GetPathName());
			}
		}
	}

	void Uninstall()
	{
		if (!GDataObjectsInstalled)
		{
			return;
		}
		if (GEndDataObjectSerializeHandler == &HandleSerialize)
		{
			GEndDataObjectSerializeHandler = GPreviousSerializeHandler;
		}
		GPreviousSerializeHandler = nullptr;
		if (GCookModificationBound)
		{
			FGameDelegates::Get().GetCookModificationDelegate() = GPreviousCookModification;
			GPreviousCookModification.Unbind();
			GCookModificationBound = false;
		}
		GDataObjectsInstalled = false;
	}

	bool IsCookedDataObject(const UObject* Object)
	{
		const UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(Object);
		const UPackage* Package = DataObject ? DataObject->GetOutermost() : nullptr;
		return Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly | PKG_MemoryMappedAsset));
	}

	bool HasGameLayout(const UEndDataObjectBase& DataObject)
	{
#if WITH_EDITORONLY_DATA
		return DataObject.FrozenFieldNames.Num() > 0 && DataObject.FrozenFieldNames.Num() == DataObject.FrozenFieldTypes.Num();
#else
		return false;
#endif
	}

	bool BuildImage(const UEndDataObjectBase& DataObject, FImage& OutImage, FString& OutError)
	{
		if (!DataObject.RowStruct)
		{
			OutError = TEXT("it has no row struct");
			return false;
		}
#if WITH_EDITORONLY_DATA
		if (!HasGameLayout(DataObject))
		{
			OutError = TEXT("the game's row layout is unknown (import the data object from the game, or make a cooked copy editable)");
			return false;
		}
		FLayout Layout;
		if (!Layout.Build(DataObject.RowStruct, DataObject.FrozenFieldNames, DataObject.FrozenFieldTypes, OutError))
		{
			return false;
		}
		TArray<FName> RowNames;
		TArray<const uint8*> Rows;
		RowNames.Reserve(DataObject.RowMap.Num());
		Rows.Reserve(DataObject.RowMap.Num());
		for (const TPair<FName, uint8*>& Row : DataObject.RowMap)
		{
			RowNames.Add(Row.Key);
			Rows.Add(Row.Value);
		}
		return Encode(Layout, RowNames, Rows, OutImage, OutError);
#else
		OutError = TEXT("editor-only data is not available");
		return false;
#endif
	}

	void AssignDecoded(UEndDataObjectBase& DataObject, FDecoded& Decoded)
	{
		DataObject.EmptyTable();
		DataObject.RowMap.Reserve(Decoded.Rows.Num());
		for (int32 Index = 0; Index < Decoded.Rows.Num(); ++Index)
		{
			DataObject.RowMap.Add(Decoded.RowNames[Index], Decoded.Rows[Index]);
		}
		Decoded.Rows.Reset();
#if WITH_EDITORONLY_DATA
		DataObject.FrozenFieldNames = Decoded.FieldNames;
		DataObject.FrozenFieldTypes = Decoded.FieldTypes;
		if (DataObject.RowStruct)
		{
			DataObject.RowStructName = DataObject.RowStruct->GetFName();
		}
#endif
	}
}
