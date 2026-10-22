#include "RebirthDataObjectLibrary.h"
#include "RebirthCharaSpecCheck.h"

#include "RebirthDataObjectEditing.h"
#include "RebirthDataObjectFormat.h"
#include "RebirthDataObjectGame.h"
#include "RebirthDataObjectSerialization.h"

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "EndDataObjectBase.h"
#include "HAL/PlatformFilemanager.h"
#include "Interfaces/ITargetPlatform.h"
#include "Interfaces/ITargetPlatformManagerModule.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UnrealType.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthDataObjectLibrary, Log, All);

namespace RebirthDataObjectLibraryDetail
{
	/** Script callers only see the message when the call succeeds, so failures go to the log too. */
	bool Outcome(bool bSucceeded, const FString& Message)
	{
		if (bSucceeded)
		{
			UE_LOG(LogRebirthDataObjectLibrary, Display, TEXT("%s"), *Message);
		}
		else
		{
			UE_LOG(LogRebirthDataObjectLibrary, Warning, TEXT("%s"), *Message);
		}
		return bSucceeded;
	}

	bool Failed(const FString& Message)
	{
		return Outcome(false, Message);
	}

	/** Same content and the same names (case included) at the same offsets. */
	bool SameImage(const RebirthDataObjectFormat::FImage& Image, const TArray<uint8>& Content, const TMap<uint32, FName>& NamesAt)
	{
		if (Image.Content != Content)
		{
			return false;
		}
		int32 Count = 0;
		for (const TPair<FName, TArray<uint32>>& Entry : Image.Names)
		{
			for (const uint32 Offset : Entry.Value)
			{
				const FName* Found = NamesAt.Find(Offset);
				if (!Found || *Found != Entry.Key || !Found->GetPlainNameString().Equals(Entry.Key.GetPlainNameString(), ESearchCase::CaseSensitive))
				{
					return false;
				}
				++Count;
			}
		}
		return Count == NamesAt.Num();
	}

	void DiscardTransient(UEndDataObjectBase* Object)
	{
		if (Object)
		{
			Object->EmptyTable();
			Object->MarkPendingKill();
		}
	}

	UEndDataObjectBase* LoadDataObjectForScript(const FString& PackageName)
	{
		return RebirthDataObjectEditing::FindDataObject(PackageName);
	}

	uint8* FindDataObjectRow(UEndDataObjectBase* DataObject, FName RowName)
	{
		uint8** Row = DataObject ? DataObject->RowMap.Find(RowName) : nullptr;
		return Row ? *Row : nullptr;
	}

	const FProperty* FindRowField(const UEndDataObjectBase* DataObject, FName FieldName)
	{
		return DataObject && DataObject->RowStruct ? FindFProperty<FProperty>(DataObject->RowStruct, FieldName) : nullptr;
	}
}

bool URebirthDataObjectLibrary::ImportDataObjectFromGame(const FString& GamePackageName, const FString& GamePaksDirectory, const FString& TargetPackageName, FString& Message)
{
	return RebirthDataObjectLibraryDetail::Outcome(RebirthDataObjectEditing::ImportFromGame(GamePackageName, GamePaksDirectory, Message, TargetPackageName), Message);
}

bool URebirthDataObjectLibrary::MakeDataObjectEditable(const FString& PackageName, FString& Message)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	if (!DataObject)
	{
		Message = FString::Printf(TEXT("%s is not a loadable data object."), *PackageName);
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	TArray<FString> Messages;
	FString BackupFolder;
	const int32 Converted = RebirthDataObjectEditing::MakeEditable(TArray<UEndDataObjectBase*>{ DataObject }, Messages, BackupFolder);
	Message = FString::Join(Messages, TEXT("\n"));
	return RebirthDataObjectLibraryDetail::Outcome(Converted == 1, Message);
}

TArray<FName> URebirthDataObjectLibrary::GetDataObjectRowNames(const FString& PackageName)
{
	TArray<FName> Names;
	if (const UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName))
	{
		DataObject->RowMap.GetKeys(Names);
	}
	return Names;
}

TArray<FString> URebirthDataObjectLibrary::CheckCharaSpecRows(const FString& PackageName, const TArray<FName>& Rows)
{
	TArray<FString> Problems;
	const UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	if (!DataObject)
	{
		Problems.Add(FString::Printf(TEXT("%s is not a data object."), *PackageName));
	}
	else if (!RebirthCharaSpecCheck::IsCharaSpecTable(*DataObject))
	{
		Problems.Add(FString::Printf(TEXT("%s is not a CharaSpec table."), *PackageName));
	}
	else
	{
		Problems = RebirthCharaSpecCheck::Check(*DataObject, Rows);
	}
	return Problems;
}

FString URebirthDataObjectLibrary::GetDataObjectRowField(const FString& PackageName, FName RowName, FName FieldName)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	uint8* Row = RebirthDataObjectLibraryDetail::FindDataObjectRow(DataObject, RowName);
	const FProperty* Property = RebirthDataObjectLibraryDetail::FindRowField(DataObject, FieldName);
	FString Text;
	if (Row && Property)
	{
		Property->ExportTextItem(Text, Property->ContainerPtrToValuePtr<void>(Row), nullptr, nullptr, PPF_None);
	}
	return Text;
}

bool URebirthDataObjectLibrary::SetDataObjectRowField(const FString& PackageName, FName RowName, FName FieldName, const FString& Value, FString& Message)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	uint8* Row = RebirthDataObjectLibraryDetail::FindDataObjectRow(DataObject, RowName);
	const FProperty* Property = RebirthDataObjectLibraryDetail::FindRowField(DataObject, FieldName);
	if (!Row || !Property)
	{
		Message = FString::Printf(TEXT("%s has no row %s with a field %s."), *PackageName, *RowName.ToString(), *FieldName.ToString());
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	DataObject->Modify();
	if (!Property->ImportText(*Value, Property->ContainerPtrToValuePtr<void>(Row), PPF_None, DataObject))
	{
		Message = FString::Printf(TEXT("\"%s\" is not a valid value for %s."), *Value, *FieldName.ToString());
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	DataObject->MarkPackageDirty();
	Message = FString::Printf(TEXT("%s.%s set."), *RowName.ToString(), *FieldName.ToString());
	return true;
}

bool URebirthDataObjectLibrary::DuplicateDataObjectRow(const FString& PackageName, FName SourceRowName, FName NewRowName, FString& Message)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	uint8* Source = RebirthDataObjectLibraryDetail::FindDataObjectRow(DataObject, SourceRowName);
	if (!Source || NewRowName.IsNone() || DataObject->RowMap.Contains(NewRowName) || !DataObject->RowStruct)
	{
		Message = FString::Printf(TEXT("Cannot duplicate %s as %s in %s."), *SourceRowName.ToString(), *NewRowName.ToString(), *PackageName);
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	DataObject->Modify();
	uint8* Row = static_cast<uint8*>(FMemory::Malloc(DataObject->RowStruct->GetStructureSize()));
	DataObject->RowStruct->InitializeStruct(Row);
	DataObject->RowStruct->CopyScriptStruct(Row, Source);
	DataObject->RowMap.Add(NewRowName, Row);
	DataObject->MarkPackageDirty();
	Message = FString::Printf(TEXT("%s duplicated as %s (%d rows)."), *SourceRowName.ToString(), *NewRowName.ToString(), DataObject->RowMap.Num());
	return true;
}

bool URebirthDataObjectLibrary::RemoveDataObjectRow(const FString& PackageName, FName RowName, FString& Message)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	if (!RebirthDataObjectLibraryDetail::FindDataObjectRow(DataObject, RowName))
	{
		Message = FString::Printf(TEXT("%s has no row %s."), *PackageName, *RowName.ToString());
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	DataObject->Modify();
	uint8* Row = nullptr;
	DataObject->RowMap.RemoveAndCopyValue(RowName, Row);
	if (Row)
	{
		DataObject->RowStruct->DestroyStruct(Row);
		FMemory::Free(Row);
	}
	DataObject->RowMap.CompactStable();
	DataObject->MarkPackageDirty();
	Message = FString::Printf(TEXT("%s removed (%d rows)."), *RowName.ToString(), DataObject->RowMap.Num());
	return true;
}

bool URebirthDataObjectLibrary::SaveDataObject(const FString& PackageName, FString& Message)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	if (!DataObject || RebirthDataObjects::IsCookedDataObject(DataObject))
	{
		Message = FString::Printf(TEXT("%s is not an editable data object."), *PackageName);
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	UPackage* Package = DataObject->GetOutermost();
	const FString Filename = FPaths::ConvertRelativePathToFull(FPackageName::LongPackageNameToFilename(Package->GetName(), FPackageName::GetAssetPackageExtension()));
	if (!UPackage::SavePackage(Package, DataObject, RF_Public | RF_Standalone, *Filename, GError, nullptr, false, true, SAVE_NoError))
	{
		Message = FString::Printf(TEXT("Saving %s failed."), *Filename);
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	Message = FString::Printf(TEXT("Saved %s (%d rows)."), *Filename, DataObject->RowMap.Num());
	return true;
}

bool URebirthDataObjectLibrary::CookDataObjectToFile(const FString& PackageName, const FString& Filename, FString& Message)
{
	UEndDataObjectBase* DataObject = RebirthDataObjectLibraryDetail::LoadDataObjectForScript(PackageName);
	if (!DataObject)
	{
		Message = FString::Printf(TEXT("%s is not a loadable data object."), *PackageName);
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	const ITargetPlatform* Platform = GetTargetPlatformManagerRef().FindTargetPlatform(TEXT("WindowsNoEditor"));
	if (!Platform)
	{
		Message = TEXT("The WindowsNoEditor target platform is not available.");
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	UPackage* Package = DataObject->GetOutermost();
	const uint32 PackageFlags = Package->GetPackageFlags();
	Package->SetPackageFlags(PKG_FilterEditorOnly);
	const FString FullFilename = FPaths::ConvertRelativePathToFull(Filename);
	IPlatformFile::GetPlatformPhysical().CreateDirectoryTree(*FPaths::GetPath(FullFilename));
	const bool bSaved = UPackage::SavePackage(Package, DataObject, RF_Public | RF_Standalone, *FullFilename, GError, nullptr, false, true,
		SAVE_NoError | SAVE_KeepGUID | SAVE_Unversioned, Platform);
	Package->SetPackageFlagsTo(PackageFlags);
	Message = bSaved ? FString::Printf(TEXT("Cooked %s (%d rows) to %s."), *PackageName, DataObject->RowMap.Num(), *FullFilename)
		: FString::Printf(TEXT("Cooking %s to %s failed."), *PackageName, *FullFilename);
	return RebirthDataObjectLibraryDetail::Outcome(bSaved, Message);
}

bool URebirthDataObjectLibrary::VerifyGameDataObjects(const FString& GamePaksDirectory, const FString& ReportFile, FString& Message)
{
	using namespace RebirthDataObjectFormat;
	using RebirthDataObjectLibraryDetail::SameImage;
	using RebirthDataObjectLibraryDetail::DiscardTransient;

	const FString Paks = GamePaksDirectory.IsEmpty() ? RebirthDataObjectGame::FindPaksDirectory(false) : GamePaksDirectory;
	TArray<RebirthDataObjectGame::FGameFile> Files;
	FString Error;
	if (Paks.IsEmpty())
	{
		Message = TEXT("The game's Paks folder was not found.");
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}
	if (!RebirthDataObjectGame::ListDataObjects(Paks, Files, Error))
	{
		Message = Error;
		return RebirthDataObjectLibraryDetail::Failed(Message);
	}

	RebirthDataObjectGame::FGameReader Reader;
	TMap<FString, int32> Counts;
	TArray<TSharedPtr<FJsonValue>> Problems;
	int64 TotalRows = 0;
	const double StartTime = FPlatformTime::Seconds();
	for (const RebirthDataObjectGame::FGameFile& File : Files)
	{
		FString Result = TEXT("ok");
		FString Detail;
		FString ClassName;
		int32 NumRows = 0;
		TArray<uint8> Bytes;
		RebirthDataObjectGame::FGameDataObject Game;
		if (!Reader.Read(File, Bytes, Detail))
		{
			Result = TEXT("read_failed");
		}
		else if (!RebirthDataObjectGame::DecodePackage(Bytes, Game, Detail))
		{
			Result = TEXT("decode_failed");
		}
		else
		{
			ClassName = Game.Class->GetName();
			NumRows = Game.Decoded.Rows.Num();
			const UScriptStruct* RowStruct = Game.Class->GetDefaultObject<UEndDataObjectBase>()->RowStruct;

			// 1. The decoded rows rebuild the game's bytes.
			FLayout Layout;
			FImage Rebuilt;
			TArray<const uint8*> Rows;
			for (uint8* Row : Game.Decoded.Rows)
			{
				Rows.Add(Row);
			}
			if (!Layout.Build(RowStruct, Game.Decoded.FieldNames, Game.Decoded.FieldTypes, Detail))
			{
				Result = TEXT("layout_failed");
			}
			else if (!Encode(Layout, Game.Decoded.RowNames, Rows, Rebuilt, Detail))
			{
				Result = TEXT("encode_failed");
			}
			else if (!SameImage(Rebuilt, Game.Content, Game.NamesAt))
			{
				Result = TEXT("rebuild_differs");
			}

			// 2. Held by a data object, cooking writes the game's bytes.
			UEndDataObjectBase* Object = NewObject<UEndDataObjectBase>(GetTransientPackage(), Game.Class, NAME_None, RF_Transient);
			RebirthDataObjects::AssignDecoded(*Object, Game.Decoded);
			if (Result == TEXT("ok"))
			{
				FImage Cooked;
				if (!RebirthDataObjects::BuildImage(*Object, Cooked, Detail))
				{
					Result = TEXT("cook_failed");
				}
				else if (!SameImage(Cooked, Game.Content, Game.NamesAt))
				{
					Result = TEXT("cook_differs");
				}
			}

			// 3. Saved and loaded the way an editable asset is, it still cooks to the game's bytes.
			if (Result == TEXT("ok"))
			{
				TArray<uint8> Saved;
				{
					FObjectWriter Writer(Object, Saved);
				}
				UEndDataObjectBase* Loaded = NewObject<UEndDataObjectBase>(GetTransientPackage(), Game.Class, NAME_None, RF_Transient);
				{
					FObjectReader ReaderArchive(Loaded, Saved);
				}
				FImage Reloaded;
				if (Loaded->RowMap.Num() != Object->RowMap.Num())
				{
					Result = TEXT("editor_rows_differ");
					Detail = FString::Printf(TEXT("%d rows saved, %d loaded"), Object->RowMap.Num(), Loaded->RowMap.Num());
				}
				else if (!RebirthDataObjects::BuildImage(*Loaded, Reloaded, Detail))
				{
					Result = TEXT("editor_cook_failed");
				}
				else if (!SameImage(Reloaded, Game.Content, Game.NamesAt))
				{
					Result = TEXT("editor_roundtrip_differs");
				}
				DiscardTransient(Loaded);
			}
			DiscardTransient(Object);
		}
		TotalRows += NumRows;
		Counts.FindOrAdd(Result)++;
		if (Result != TEXT("ok"))
		{
			TSharedRef<FJsonObject> Problem = MakeShared<FJsonObject>();
			Problem->SetStringField(TEXT("package"), File.PackageName);
			Problem->SetStringField(TEXT("result"), Result);
			Problem->SetStringField(TEXT("class"), ClassName);
			Problem->SetStringField(TEXT("detail"), Detail);
			Problems.Add(MakeShared<FJsonValueObject>(Problem));
		}
	}
	CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

	const int32 Passed = Counts.FindRef(TEXT("ok"));
	TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
	Report->SetNumberField(TEXT("data_objects"), Files.Num());
	Report->SetNumberField(TEXT("passed"), Passed);
	Report->SetNumberField(TEXT("rows"), double(TotalRows));
	Report->SetNumberField(TEXT("seconds"), FPlatformTime::Seconds() - StartTime);
	TSharedRef<FJsonObject> CountObject = MakeShared<FJsonObject>();
	for (const TPair<FString, int32>& Count : Counts)
	{
		CountObject->SetNumberField(Count.Key, Count.Value);
	}
	Report->SetObjectField(TEXT("results"), CountObject);
	Report->SetArrayField(TEXT("problems"), Problems);
	if (!ReportFile.IsEmpty())
	{
		FString Json;
		const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Json);
		FJsonSerializer::Serialize(Report, JsonWriter);
		FFileHelper::SaveStringToFile(Json, *ReportFile);
	}
	Message = FString::Printf(TEXT("%d of %d game data objects (%lld rows) read, saved, reloaded and cooked back to the game's exact bytes."), Passed, Files.Num(), TotalRows);
	return RebirthDataObjectLibraryDetail::Outcome(Passed == Files.Num(), Message);
}
