// Fill out your copyright notice in the Description page of Project Settings.

#include "EndAssetPack_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndAssetPack.h"

#define LOCTEXT_NAMESPACE "UEndAssetPack_Factory"

UEndAssetPack_Factory::UEndAssetPack_Factory()
{
	Formats.Add(TEXT("xml;EndAssetPack"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndAssetPack::StaticClass();
}

FText UEndAssetPack_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Asset Pack");
}

uint32 UEndAssetPack_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndAssetPack_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndAssetPack>(InParent, InClass, InName, flags);
}

bool UEndAssetPack_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndAssetPack_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndAssetPack* ImportedAsset = NewObject<UEndAssetPack>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE