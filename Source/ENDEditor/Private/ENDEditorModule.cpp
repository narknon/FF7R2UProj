#include "ENDEditorModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_EffectAppendixMesh.h"
#include "AssetTypeActions_EndEmissiveColorSettings.h"

void FENDEditorModule::StartupModule()
{
	FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();

	IAssetTools& AssetTools = AssetToolsModule.Get();
	
	EAssetTypeCategories::Type CustomAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName("SQEX"), FText::FromString("SQEX"));
	AssetAction = new FAssetTypeActions_EndEmissiveColorSettings(CustomAssetCategory);
	AssetAction2 = new FAssetTypeActions_EffectAppendixMesh(CustomAssetCategory);
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction2));
}

void FENDEditorModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
		IAssetTools& AssetTools = AssetToolsModule.Get();
		AssetTools.UnregisterAssetTypeActions(AssetAction->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction2->AsShared());
	}
}
	
IMPLEMENT_MODULE(FENDEditorModule, ENDEditor)