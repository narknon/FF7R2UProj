#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RebirthCookAssetManagerProxy.generated.h"

/**
 * Stands in for the engine's asset manager only between the cook modification delegate and UAssetManager::ModifyCook
 * (RebirthCookedTextureSkip). ModifyCook puts the real asset manager back, runs its ModifyCook unchanged, then adds
 * ExtraNeverCookPackages to the NeverCook output. The proxy never initializes asset manager state of its own.
 */
UCLASS(Transient, NotBlueprintable)
class URebirthCookAssetManagerProxy : public UAssetManager
{
	GENERATED_BODY()

public:
	/** Deliberately skips UAssetManager::PostInitProperties, which binds global delegates to the manager being set up. */
	virtual void PostInitProperties() override;

	/** Puts the real asset manager back, runs its ModifyCook, then adds ExtraNeverCookPackages. */
	virtual void ModifyCook(TArray<FName>& PackagesToCook, TArray<FName>& PackagesToNeverCook) override;

	/** The engine's asset manager, restored by ModifyCook. */
	UPROPERTY(Transient)
	UAssetManager* RealAssetManager = nullptr;

	/** Long package names (/Game/..., /Engine/...) the cooker must not cook. */
	TArray<FName> ExtraNeverCookPackages;
};
