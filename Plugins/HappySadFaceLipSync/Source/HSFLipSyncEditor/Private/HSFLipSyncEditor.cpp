// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "HSFLipSyncEditor.h"
#include "HSFLipSyncEditorEdMode.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "FHSFLipSyncEditorModule"

void FHSFLipSyncEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FHSFLipSyncEditorEdMode>(FHSFLipSyncEditorEdMode::EM_HSFLipSyncEditorEdModeId, LOCTEXT("HSFLipSyncEditorEdModeName", "HSFLipSyncEditorEdMode"), FSlateIcon(), true);
	
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShared<FAssetTypeActions_HSFLipMap>());
	AssetTools.RegisterAssetTypeActions(MakeShared<FAssetTypeActions_HSFLipSyncDataPack>());
}

void FHSFLipSyncEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FHSFLipSyncEditorEdMode::EM_HSFLipSyncEditorEdModeId);
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHSFLipSyncEditorModule, HSFLipSyncEditor)