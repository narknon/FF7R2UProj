#include "ENDEditorModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_EffectAppendixMesh.h"
#include "AssetTypeActions_EndEmissiveColorSettings.h"
#include "AssetTypeActions_EndCinemaSequence.h"
#include "AssetTypeActions_EndCameraSequence.h"
#include "AssetTypeActions_ShaderResourceBuffer.h"
#include "AssetTypeActions_EndAssetPack.h"
#include "AssetTypeActions_EndAnimSet.h"

void FENDEditorModule::StartupModule()
{
	FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();

	IAssetTools& AssetTools = AssetToolsModule.Get();
	
	EAssetTypeCategories::Type CustomAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName("SQEX"), FText::FromString("SQEX"));
	AssetAction = new FAssetTypeActions_EndEmissiveColorSettings(CustomAssetCategory);
	AssetAction2 = new FAssetTypeActions_EffectAppendixMesh(CustomAssetCategory);
	AssetAction3 = new FAssetTypeActions_EndCameraSequence(CustomAssetCategory);
	AssetAction4 = new FAssetTypeActions_EndCinemaSequence(CustomAssetCategory);
	AssetAction5 = new FAssetTypeActions_EndAnimSet(CustomAssetCategory);
	AssetAction6 = new FAssetTypeActions_EndAssetPack(CustomAssetCategory);
	AssetAction7 = new FAssetTypeActions_ShaderResourceBuffer(CustomAssetCategory);
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction2));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction3));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction4));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction5));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction6));
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction7));
}

void FENDEditorModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
		IAssetTools& AssetTools = AssetToolsModule.Get();
		AssetTools.UnregisterAssetTypeActions(AssetAction->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction2->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction3->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction4->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction5->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction6->AsShared());
		AssetTools.UnregisterAssetTypeActions(AssetAction7->AsShared());
	}
}
	
IMPLEMENT_MODULE(FENDEditorModule, ENDEditor)