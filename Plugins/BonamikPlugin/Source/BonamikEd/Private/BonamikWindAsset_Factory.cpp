// Fill out your copyright notice in the Description page of Project Settings.

#include "BonamikWindAsset_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "SQEX_BonamikWind_Asset.h"

#define LOCTEXT_NAMESPACE "UBonamikWindAsset_Factory"

UBonamikWindAsset_Factory::UBonamikWindAsset_Factory()
{
	Formats.Add(TEXT("xml;BonamikWindAsset"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = USQEX_BonamikWind_Asset::StaticClass();
}

FText UBonamikWindAsset_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "Bonamik Wind Asset");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 UBonamikWindAsset_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("Bonamik", LOCTEXT("AssetCategoryName", "Bonamik"));
}

UObject * UBonamikWindAsset_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<USQEX_BonamikWind_Asset>(InParent, InClass, InName, flags);
}

bool UBonamikWindAsset_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UBonamikWindAsset_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	USQEX_BonamikWind_Asset* ImportedAsset = NewObject<USQEX_BonamikWind_Asset>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE