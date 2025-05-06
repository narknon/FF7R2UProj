// Fill out your copyright notice in the Description page of Project Settings.

#include "EndFont_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndFont.h"

#define LOCTEXT_NAMESPACE "UEndFont_Factory"

UEndFont_Factory::UEndFont_Factory()
{
	Formats.Add(TEXT("xml;EndFont"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndFont::StaticClass();
}

FText UEndFont_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Font");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 UEndFont_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndFont_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndFont>(InParent, InClass, InName, flags);
}

bool UEndFont_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndFont_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndFont* ImportedAsset = NewObject<UEndFont>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE