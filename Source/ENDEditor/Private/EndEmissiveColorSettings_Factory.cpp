// Fill out your copyright notice in the Description page of Project Settings.

#include "EndEmissiveColorSettings_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndEmissiveColorSettings.h"

#define LOCTEXT_NAMESPACE "UEndEmissiveColorSettings_Factory"

UEndEmissiveColorSettings_Factory::UEndEmissiveColorSettings_Factory()
{
	Formats.Add(TEXT("xml;EndEmissiveColorSettings"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndEmissiveColorSettings::StaticClass();
}

FText UEndEmissiveColorSettings_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Emissive Color Settings");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 UEndEmissiveColorSettings_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndEmissiveColorSettings_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndEmissiveColorSettings>(InParent, InClass, InName, flags);
}

bool UEndEmissiveColorSettings_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndEmissiveColorSettings_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndEmissiveColorSettings* ImportedAsset = NewObject<UEndEmissiveColorSettings>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE