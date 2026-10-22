#include "RebirthCharaSpecCheck.h"

#include "RebirthDataObjectFormat.h"
#include "RebirthDataObjectGame.h"
#include "RebirthGameAssets.h"
#include "RebirthPackageHeader.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "EndDataObjectBase.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Logging/LogMacros.h"
#include "Misc/PackageName.h"
#include "Modules/ModuleManager.h"
#include "UObject/Package.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectHash.h"
#include "Widgets/Notifications/SNotificationList.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthCharaSpecCheck, Log, All);

namespace RebirthCharaSpecCheckDetail
{
	const TCHAR* const GameTablePackage = TEXT("/Game/DataObject/Resident/CharaSpec");
	const TCHAR* const DataAssetPrefix = TEXT("/Game/DataAsset/Game/CharaSpec/CharaSpec_");
	const FName RowStructName(TEXT("EndDataTableCharaSpec"));

	FDelegateHandle GSavedHandle;

	FName NameField(const UScriptStruct* Struct, const uint8* Row, const TCHAR* Field)
	{
		const FNameProperty* Property = FindFProperty<FNameProperty>(Struct, Field);
		return Property ? Property->GetPropertyValue_InContainer(Row) : NAME_None;
	}

	TArray<FName> NameArrayField(const UScriptStruct* Struct, const uint8* Row, const TCHAR* Field)
	{
		TArray<FName> Out;
		const FArrayProperty* Property = FindFProperty<FArrayProperty>(Struct, Field);
		if (Property && Property->Inner && Property->Inner->IsA<FNameProperty>())
		{
			FScriptArrayHelper Helper(Property, Property->ContainerPtrToValuePtr<void>(Row));
			for (int32 Index = 0; Index < Helper.Num(); ++Index)
			{
				Out.Add(*reinterpret_cast<const FName*>(Helper.GetRawPtr(Index)));
			}
		}
		return Out;
	}

	/** Anim set names by motion folder: /Game/Motion/<...>/<Folder>/<Set>, from the game and this project. */
	TMap<FName, TSet<FName>> GMotionSets;
	bool GMotionSetsBuilt = false;

	void AddMotionPackage(const FString& PackageName)
	{
		if (!PackageName.StartsWith(TEXT("/Game/Motion/")))
		{
			return;
		}
		int32 Last = INDEX_NONE;
		if (!PackageName.FindLastChar(TEXT('/'), Last) || Last <= 0)
		{
			return;
		}
		const FString Parent = PackageName.Left(Last);
		int32 ParentSlash = INDEX_NONE;
		if (!Parent.FindLastChar(TEXT('/'), ParentSlash))
		{
			return;
		}
		GMotionSets.FindOrAdd(FName(*Parent.Mid(ParentSlash + 1))).Add(FName(*PackageName.Mid(Last + 1)));
	}

	bool BuildMotionSets(FString& OutError)
	{
		if (GMotionSetsBuilt)
		{
			return true;
		}
		RebirthGameAssets::FGameIndex& Game = RebirthGameAssets::FGameIndex::Get();
		if (!Game.Initialize(OutError))
		{
			return false;
		}
		TArray<FName> Names;
		Game.GetPackageNames(Names);
		for (const FName& Name : Names)
		{
			AddMotionPackage(Name.ToString());
		}
		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
		TArray<FAssetData> Assets;
		Registry.GetAssetsByPath(FName(TEXT("/Game/Motion")), Assets, true, false);
		for (const FAssetData& Asset : Assets)
		{
			AddMotionPackage(Asset.PackageName.ToString());
		}
		GMotionSetsBuilt = true;
		return true;
	}

	/** Names in the data asset CharaSpec_<Model> that ships: an editable one in this project, else the game's. */
	bool ReadDataAssetNames(FName Model, TSet<FName>& OutNames, FString& OutWhere)
	{
		const FString PackageName = FString(DataAssetPrefix) + Model.ToString();
		FString Filename;
		if (FPackageName::DoesPackageExist(PackageName, nullptr, &Filename))
		{
			RebirthPackageHeader::FHeader Header;
			FString Error;
			if (RebirthPackageHeader::Read(Filename, Header, false, Error) && !Header.IsCooked())
			{
				OutNames = TSet<FName>(Header.Names);
				OutWhere = TEXT("this project's");
				return true;
			}
			// A cooked copy in the project is not packaged; the game uses its own file.
		}
		RebirthGameAssets::FGameIndex& Game = RebirthGameAssets::FGameIndex::Get();
		FString Error;
		const FName Package(*PackageName);
		if (Game.Initialize(Error) && Game.Contains(Package))
		{
			RebirthGameAssets::FZenPackage Zen;
			if (Game.ReadZenPackage(Package, Zen, Error))
			{
				OutNames = TSet<FName>(Zen.Names);
				OutWhere = TEXT("the game's");
				return true;
			}
		}
		return false;
	}

	void CheckRow(const UEndDataObjectBase& DataObject, FName RowName, const uint8* Row, TMap<FName, FString>& DataAssetCache, TArray<FString>& Out)
	{
		const UScriptStruct* Struct = DataObject.GetRowStruct();
		const FString Name = RowName.ToString();

		// The data asset of the model: entries <Model>_Class (blueprint, AI) and <Model>_Data (anim sets, sounds...).
		const FName Model = NameField(Struct, Row, TEXT("ContentsModel"));
		if (Model.IsNone())
		{
			Out.Add(FString::Printf(TEXT("%s: ContentsModel is empty."), *Name));
		}
		else
		{
			FString* Cached = DataAssetCache.Find(Model);
			if (!Cached)
			{
				FString Problem;
				TSet<FName> Names;
				FString Where;
				const FString AssetName = TEXT("CharaSpec_") + Model.ToString();
				if (!ReadDataAssetNames(Model, Names, Where))
				{
					Problem = FString::Printf(TEXT("ContentsModel is %s, but there is no data asset %s (DataAsset/Game/CharaSpec) in this project or the game. ")
						TEXT("Duplicate the data asset of the character you want and name it %s."), *Model.ToString(), *AssetName, *AssetName);
				}
				else
				{
					const FName ClassEntry(*(Model.ToString() + TEXT("_Class")));
					const FName DataEntry(*(Model.ToString() + TEXT("_Data")));
					TArray<FString> Missing;
					if (!Names.Contains(ClassEntry))
					{
						Missing.Add(ClassEntry.ToString());
					}
					if (!Names.Contains(DataEntry))
					{
						Missing.Add(DataEntry.ToString());
					}
					if (Missing.Num() > 0)
					{
						Problem = FString::Printf(TEXT("ContentsModel is %s, but %s data asset %s has no entry named %s (its AssetClassList/AssetDataList entries must be named after the ContentsModel)."),
							*Model.ToString(), *Where, *AssetName, *FString::Join(Missing, TEXT(" or ")));
					}
				}
				Cached = &DataAssetCache.Add(Model, Problem);
			}
			if (!Cached->IsEmpty())
			{
				Out.Add(FString::Printf(TEXT("%s: %s"), *Name, **Cached));
			}
		}

		// Anim sets: /Game/Motion/.../<AnimationSetParentFolder>/<set>.
		const FName Folder = NameField(Struct, Row, TEXT("AnimationSetParentFolder"));
		TArray<FName> Sets = NameArrayField(Struct, Row, TEXT("AnimationSetList_Array"));
		Sets.RemoveAll([](const FName& Set) { return Set.IsNone(); });
		if (Sets.Num() > 0)
		{
			FString Error;
			if (Folder.IsNone())
			{
				Out.Add(FString::Printf(TEXT("%s: AnimationSetList has entries but AnimationSetParentFolder is empty."), *Name));
			}
			else if (BuildMotionSets(Error))
			{
				const TSet<FName>* Known = GMotionSets.Find(Folder);
				if (!Known)
				{
					Out.Add(FString::Printf(TEXT("%s: AnimationSetParentFolder %s is not a motion folder of the game or this project (they are named like PC0000_Cloud or PC0011_Vincent)."),
						*Name, *Folder.ToString()));
				}
				else
				{
					TArray<FString> Missing;
					for (const FName& Set : Sets)
					{
						if (!Known->Contains(Set))
						{
							Missing.Add(Set.ToString());
						}
					}
					if (Missing.Num() > 0)
					{
						TArray<FString> Available;
						for (const FName& Set : *Known)
						{
							Available.Add(Set.ToString());
						}
						Available.Sort();
						Out.Add(FString::Printf(TEXT("%s: motion folder %s has no anim set %s (it has %s)."),
							*Name, *Folder.ToString(), *FString::Join(Missing, TEXT(", ")), *FString::Join(Available, TEXT(", "))));
					}
				}
			}
		}

		// Other rows of the table.
		auto CheckRowReference = [&](const TCHAR* Field, FName Referenced)
		{
			if (!Referenced.IsNone() && !DataObject.GetRowMap().Contains(Referenced))
			{
				Out.Add(FString::Printf(TEXT("%s: %s refers to row %s, which is not in this table."), *Name, Field, *Referenced.ToString()));
			}
		};
		CheckRowReference(TEXT("NoBattleCharaSpec"), NameField(Struct, Row, TEXT("NoBattleCharaSpec")));
		CheckRowReference(TEXT("ReserveCharaSpec"), NameField(Struct, Row, TEXT("ReserveCharaSpec")));
		for (const FName& Referenced : NameArrayField(Struct, Row, TEXT("EquipmentCharaSpecList_Array")))
		{
			CheckRowReference(TEXT("EquipmentCharaSpecList"), Referenced);
		}
		for (const FName& Referenced : NameArrayField(Struct, Row, TEXT("SharedCharaSpecList_Array")))
		{
			CheckRowReference(TEXT("SharedCharaSpecList"), Referenced);
		}
	}

	void Notify(const FString& Text, bool bProblem)
	{
		if (!GIsEditor || IsRunningCommandlet() || !FSlateApplication::IsInitialized())
		{
			return;
		}
		FNotificationInfo Info(FText::FromString(Text));
		Info.ExpireDuration = bProblem ? 12.f : 4.f;
		Info.bUseLargeFont = false;
		if (TSharedPtr<SNotificationItem> Item = FSlateNotificationManager::Get().AddNotification(Info))
		{
			Item->SetCompletionState(bProblem ? SNotificationItem::CS_Fail : SNotificationItem::CS_Success);
		}
	}

	void OnPackageSaved(const FString& Filename, UObject* Outer)
	{
		UPackage* Package = Cast<UPackage>(Outer);
		if (!Package || IsRunningCommandlet())
		{
			return;
		}
		TArray<UObject*> Objects;
		GetObjectsWithOuter(Package, Objects, false);
		for (UObject* Object : Objects)
		{
			if (const UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(Object))
			{
				if (RebirthCharaSpecCheck::IsCharaSpecTable(*DataObject))
				{
					RebirthCharaSpecCheck::CheckAndReport(*DataObject, true);
				}
			}
		}
	}
}

namespace RebirthCharaSpecCheck
{
	using namespace RebirthCharaSpecCheckDetail;

	bool IsCharaSpecTable(const UEndDataObjectBase& DataObject)
	{
		const UScriptStruct* Struct = DataObject.GetRowStruct();
		return Struct && Struct->GetFName() == RowStructName;
	}

	TArray<FName> GetChangedRows(const UEndDataObjectBase& DataObject)
	{
		TArray<FName> All;
		for (const auto& Row : DataObject.GetRowMap())
		{
			All.Add(Row.Key);
		}
		const UScriptStruct* Struct = DataObject.GetRowStruct();
		RebirthGameAssets::FGameIndex& Game = RebirthGameAssets::FGameIndex::Get();
		FString Error;
		TArray<uint8> Bytes;
		if (!Struct || !Game.Initialize(Error) || !Game.ReadPackage(FName(GameTablePackage), Bytes, Error))
		{
			return All;
		}
		RebirthDataObjectGame::FGameDataObject GameTable;
		if (!RebirthDataObjectGame::DecodePackage(Bytes, GameTable, Error))
		{
			return All;
		}
		const UEndDataObjectBase* Defaults = GameTable.Class ? GameTable.Class->GetDefaultObject<UEndDataObjectBase>() : nullptr;
		const UScriptStruct* GameStruct = Defaults ? Defaults->RowStruct : nullptr;
		TArray<FName> Changed;
		if (GameStruct == Struct)
		{
			TMap<FName, const uint8*> GameRows;
			for (int32 Index = 0; Index < GameTable.Decoded.RowNames.Num(); ++Index)
			{
				GameRows.Add(GameTable.Decoded.RowNames[Index], GameTable.Decoded.Rows[Index]);
			}
			for (const auto& Row : DataObject.GetRowMap())
			{
				const uint8* const* GameRow = GameRows.Find(Row.Key);
				if (!GameRow || !Struct->CompareScriptStruct(Row.Value, *GameRow, PPF_None))
				{
					Changed.Add(Row.Key);
				}
			}
		}
		else
		{
			Changed = All;
		}
		RebirthDataObjectFormat::FreeRows(GameStruct, GameTable.Decoded.Rows);
		return Changed;
	}

	TArray<FString> Check(const UEndDataObjectBase& DataObject, const TArray<FName>& Rows)
	{
		TArray<FString> Problems;
		if (!IsCharaSpecTable(DataObject))
		{
			return Problems;
		}
		const TArray<FName> ToCheck = Rows.Num() > 0 ? Rows : GetChangedRows(DataObject);
		TMap<FName, FString> DataAssetCache;
		for (const FName& RowName : ToCheck)
		{
			const uint8* Row = DataObject.FindRowUnchecked(RowName);
			if (!Row)
			{
				Problems.Add(FString::Printf(TEXT("%s: no such row."), *RowName.ToString()));
				continue;
			}
			CheckRow(DataObject, RowName, Row, DataAssetCache, Problems);
		}
		return Problems;
	}

	TArray<FString> CheckAndReport(const UEndDataObjectBase& DataObject, bool bNotify)
	{
		const TArray<FName> Changed = GetChangedRows(DataObject);
		const TArray<FString> Problems = Changed.Num() > 0 ? Check(DataObject, Changed) : TArray<FString>();
		const FString Path = DataObject.GetPathName();
		if (Problems.Num() == 0)
		{
			UE_LOG(LogRebirthCharaSpecCheck, Display, TEXT("%s: %d changed row(s) checked, no problems."), *Path, Changed.Num());
			if (bNotify && Changed.Num() > 0)
			{
				Notify(FString::Printf(TEXT("CharaSpec check: %d changed row(s), no problems."), Changed.Num()), false);
			}
			return Problems;
		}
		UE_LOG(LogRebirthCharaSpecCheck, Warning, TEXT("%s: %d problem(s) in %d changed row(s). The game waits on the loading screen forever when a CharaSpec refers to something it can't find:"),
			*Path, Problems.Num(), Changed.Num());
		for (const FString& Problem : Problems)
		{
			UE_LOG(LogRebirthCharaSpecCheck, Warning, TEXT("  %s"), *Problem);
		}
		if (bNotify)
		{
			Notify(FString::Printf(TEXT("CharaSpec check: %d problem(s) that would hang the game's loading screen.\n%s%s\nDetails: Output Log, LogRebirthCharaSpecCheck."),
				Problems.Num(), *Problems[0], Problems.Num() > 1 ? TEXT("\n...") : TEXT("")), true);
		}
		return Problems;
	}

	void Register()
	{
		if (!GSavedHandle.IsValid())
		{
			GSavedHandle = UPackage::PackageSavedEvent.AddStatic(&OnPackageSaved);
		}
	}

	void Unregister()
	{
		if (GSavedHandle.IsValid())
		{
			UPackage::PackageSavedEvent.Remove(GSavedHandle);
			GSavedHandle.Reset();
		}
	}
}
