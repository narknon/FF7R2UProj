// Fill out your copyright notice in the Description page of Project Settings.

#include "ShaderResourceBuffer_Factory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"
#include "ShaderResourceBuffer.h"

#define LOCTEXT_NAMESPACE "UShaderResourceBuffer_Factory"

UShaderResourceBuffer_Factory::UShaderResourceBuffer_Factory()
{
	Formats.Add(TEXT("xml;ShaderResourceBuffer"));
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = true;
	SupportedClass = UShaderResourceBuffer::StaticClass();
}

FText UShaderResourceBuffer_Factory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "Shader Resource Buffer");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 UShaderResourceBuffer_Factory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("SQEX", LOCTEXT("AssetCategoryName", "SQEX"));
}

UObject * UShaderResourceBuffer_Factory::FactoryCreateNew(UClass * InClass, UObject * InParent, FName InName, EObjectFlags flags, UObject * Cntext, FFeedbackContext * Warn)
{
	return NewObject<UShaderResourceBuffer>(InParent, InClass, InName, flags);
}

bool UShaderResourceBuffer_Factory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UShaderResourceBuffer_Factory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UShaderResourceBuffer* ImportedAsset = NewObject<UShaderResourceBuffer>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}

#undef  LOCTEXT_NAMESPACE