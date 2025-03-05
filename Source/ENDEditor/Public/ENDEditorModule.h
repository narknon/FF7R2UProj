#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FENDEditorModule : public IModuleInterface
{
public:
	FENDEditorModule() {}
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	class FAssetTypeActions_EndEmissiveColorSettings* AssetAction;
	class FAssetTypeActions_EffectAppendixMesh* AssetAction2;
	class FAssetTypeActions_EndCameraSequence* AssetAction3;
	class FAssetTypeActions_EndCinemaSequence* AssetAction4;
	class FAssetTypeActions_EndAnimSet* AssetAction5;
	class FAssetTypeActions_EndAssetPack* AssetAction6;
	class FAssetTypeActions_ShaderResourceBuffer* AssetAction7;
};