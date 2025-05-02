// Fill out your copyright notice in the Description page of Project Settings.

#include "SQEXSEADSound_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "SQEXSEADSound.h"

#define LOCTEXT_NAMESPACE "USQEXSEADSound_Factory"

USQEXSEADSound_Factory::USQEXSEADSound_Factory()
{
	Formats.Add(TEXT("xml;SQEXSEADSound"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = USQEXSEADSound::StaticClass();
}

FText USQEXSEADSound_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "SQEXSEAD Sound");
}

uint32 USQEXSEADSound_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEXSEAD", LOCTEXT("AssetCategoryName", "SQEXSEAD"));
}

UObject * USQEXSEADSound_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<USQEXSEADSound>(InParent, InClass, InName, flags);
}

bool USQEXSEADSound_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* USQEXSEADSound_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	USQEXSEADSound* ImportedAsset = NewObject<USQEXSEADSound>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE