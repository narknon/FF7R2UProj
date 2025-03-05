// Fill out your copyright notice in the Description page of Project Settings.

#include "EndCameraSequence_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndCameraSequence.h"

#define LOCTEXT_NAMESPACE "UEndCameraSequence_Factory"

UEndCameraSequence_Factory::UEndCameraSequence_Factory()
{
	Formats.Add(TEXT("xml;EndAssetPack"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndCameraSequence::StaticClass();
}

FText UEndCameraSequence_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Camera Sequence");
}

uint32 UEndCameraSequence_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndCameraSequence_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndCameraSequence>(InParent, InClass, InName, flags);
}

bool UEndCameraSequence_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndCameraSequence_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndCameraSequence* ImportedAsset = NewObject<UEndCameraSequence>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE