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
};