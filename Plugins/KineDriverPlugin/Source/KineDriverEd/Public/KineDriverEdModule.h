#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FKineDriverEdModule : public IModuleInterface
{
public:
	FKineDriverEdModule() {}
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	class FAssetTypeActions_KineDriverData* AssetAction;
};