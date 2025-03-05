// Fill out your copyright notice in the Description page of Project Settings.

#include "EndCinemaSequence_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EndCinemaSequence.h"

#define LOCTEXT_NAMESPACE "UEndCinemaSequence_Factory"

UEndCinemaSequence_Factory::UEndCinemaSequence_Factory()
{
	Formats.Add(TEXT("xml;EndAssetPack"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEndCinemaSequence::StaticClass();
}

FText UEndCinemaSequence_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "End Cinema Sequence");
}

uint32 UEndCinemaSequence_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEndCinemaSequence_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEndCinemaSequence>(InParent, InClass, InName, flags);
}

bool UEndCinemaSequence_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEndCinemaSequence_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEndCinemaSequence* ImportedAsset = NewObject<UEndCinemaSequence>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE