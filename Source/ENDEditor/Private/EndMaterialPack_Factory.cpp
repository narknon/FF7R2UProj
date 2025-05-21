// Fill out your copyright notice in the Description page of Project Settings.

#include "EndMaterialPack_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndMaterialPack.h"

#define LOCTEXT_NAMESPACE "UEndMaterialPack_Factory"

UEndMaterialPack_Factory::UEndMaterialPack_Factory()
{
	Formats.Add(TEXT("xml;EndMaterialPack"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndMaterialPack::StaticClass();
}

FText UEndMaterialPack_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Material Pack");
}

uint32 UEndMaterialPack_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndMaterialPack_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndMaterialPack>(InParent, InClass, InName, flags);
}

bool UEndMaterialPack_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndMaterialPack_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndMaterialPack* ImportedAsset = NewObject<UEndMaterialPack>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE