#include "KineDriverEdModule.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_KineDriverData.h"

void FKineDriverEdModule::StartupModule()
{
	FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();

	IAssetTools& AssetTools = AssetToolsModule.Get();
	
	EAssetTypeCategories::Type CustomAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName("SQEX"), FText::FromString("SQEX"));
	AssetAction = new FAssetTypeActions_KineDriverData(CustomAssetCategory);
	AssetTools.RegisterAssetTypeActions(MakeShareable(AssetAction));
}

void FKineDriverEdModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		FAssetToolsModule& AssetToolsModule = FAssetToolsModule::GetModule();
		IAssetTools& AssetTools = AssetToolsModule.Get();
		AssetTools.UnregisterAssetTypeActions(AssetAction->AsShared());
	}
}
	
IMPLEMENT_MODULE(FKineDriverEdModule, KineDriverEd)