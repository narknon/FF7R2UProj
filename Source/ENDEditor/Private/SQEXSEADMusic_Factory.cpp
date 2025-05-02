// Fill out your copyright notice in the Description page of Project Settings.

#include "SQEXSEADMusic_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "SQEXSEADMusic.h"

#define LOCTEXT_NAMESPACE "USQEXSEADMusic_Factory"

USQEXSEADMusic_Factory::USQEXSEADMusic_Factory()
{
	Formats.Add(TEXT("xml;SQEXSEADMusic"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = USQEXSEADMusic::StaticClass();
}

FText USQEXSEADMusic_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "SQEXSEAD Music");
}

uint32 USQEXSEADMusic_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEXSEAD", LOCTEXT("AssetCategoryName", "SQEXSEAD"));
}

UObject * USQEXSEADMusic_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<USQEXSEADMusic>(InParent, InClass, InName, flags);
}

bool USQEXSEADMusic_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* USQEXSEADMusic_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	USQEXSEADMusic* ImportedAsset = NewObject<USQEXSEADMusic>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE