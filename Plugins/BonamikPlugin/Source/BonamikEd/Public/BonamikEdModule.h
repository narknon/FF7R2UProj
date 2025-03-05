#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBonamikEdModule : public IModuleInterface
{
public:
	FBonamikEdModule() {}
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	class FAssetTypeActions_BonamikWindAsset* AssetAction;
};