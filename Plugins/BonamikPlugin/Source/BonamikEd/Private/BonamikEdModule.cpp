#include "BonamikEdModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_BonamikWindAsset.h"

void FBonamikEdModule::StartupModule()
{
	FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();

	IAssetTools& AssetTools = AssetToolsModule.Get();

	EAssetTypeCategories::Type CustomAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName("Bonamik"), FText::FromString("Bonamik"));
	AssetAction = new FAssetTypeActions_BonamikWindAsset(CustomAssetCategory);
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction));
}

void FBonamikEdModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
		IAssetTools& AssetTools = AssetToolsModule.Get();
		AssetTools.UnregisterAssetTypeActions(AssetAction->AsShared());
	}
}

IMPLEMENT_MODULE(FBonamikEdModule, BonamikEd)