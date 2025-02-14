// Fill out your copyright notice in the Description page of Project Settings.

#include "EffectAppendixMesh_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "EffectAppendixMesh.h"

#define LOCTEXT_NAMESPACE "UEffectAppendixMesh_Factory"

UEffectAppendixMesh_Factory::UEffectAppendixMesh_Factory()
{
	Formats.Add(TEXT("xml;EffectAppendixMesh"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UEffectAppendixMesh::StaticClass();
}

FText UEffectAppendixMesh_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "Effect Appendix Mesh");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 UEffectAppendixMesh_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UEffectAppendixMesh_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UEffectAppendixMesh>(InParent, InClass, InName, flags);
}

bool UEffectAppendixMesh_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UEffectAppendixMesh_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UEffectAppendixMesh* ImportedAsset = NewObject<UEffectAppendixMesh>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE