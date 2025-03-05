// Fill out your copyright notice in the Description page of Project Settings.

#include "EndAnimSet_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndAnimSet.h"

#define LOCTEXT_NAMESPACE "UEndAnimSet_Factory"

UEndAnimSet_Factory::UEndAnimSet_Factory()
{
	Formats.Add(TEXT("xml;EndAnimSet"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndAnimSet::StaticClass();
}

FText UEndAnimSet_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Anim Set");
}

uint32 UEndAnimSet_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndAnimSet_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndAnimSet>(InParent, InClass, InName, flags);
}

bool UEndAnimSet_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndAnimSet_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndAnimSet* ImportedAsset = NewObject<UEndAnimSet>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE