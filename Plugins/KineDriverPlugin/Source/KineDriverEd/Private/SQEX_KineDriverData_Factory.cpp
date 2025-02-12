// Fill out your copyright notice in the Description page of Project Settings.

#include "SQEX_KineDriverData_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "SQEX_KineDriverData.h"

#define LOCTEXT_NAMESPACE "USQEX_KineDriverData_Factory"

USQEX_KineDriverData_Factory::USQEX_KineDriverData_Factory()
{
	Formats.Add(TEXT("xml;KineDriver Data"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = USQEX_KineDriverData::StaticClass();
}

FText USQEX_KineDriverData_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "KineDriver Data");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 USQEX_KineDriverData_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * USQEX_KineDriverData_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<USQEX_KineDriverData>(InParent, InClass, InName, flags);
}

bool USQEX_KineDriverData_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* USQEX_KineDriverData_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	USQEX_KineDriverData* ImportedAsset = NewObject<USQEX_KineDriverData>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

bool USQEX_KineDriverData_Factory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	USQEX_KineDriverData* ImportedAsset = Cast<USQEX_KineDriverData>(Obj);
	if (ImportedAsset)
	{
		return true;
	}
	return false;
}

void USQEX_KineDriverData_Factory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	USQEX_KineDriverData* ImportedAsset = Cast<USQEX_KineDriverData>(Obj);
	if (ImportedAsset && ensure(NewReimportPaths.Num() == 1))
	{
		FString FilePath = FPaths::GetPath(NewReimportPaths[0]);
		FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	}
}

EReimportResult::Type USQEX_KineDriverData_Factory::Reimport(UObject* Obj)
{
	USQEX_KineDriverData* ImportedAsset = Cast<USQEX_KineDriverData>(Obj);
	if (!ImportedAsset) { return EReimportResult::Failed; }
	bool OutCanceled = false;
	

	return EReimportResult::Succeeded;
}

#undef  LOCTEXT_NAMESPACE