// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeActions_Base.h"
#include "HSFLipMapFactory.h"
#include "HSFLipSyncDataPackFactory.h"

class FHSFLipSyncEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

class FAssetTypeActions_HSFLipMap : public FAssetTypeActions_Base {
public:
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_HSFLipMap", "HSF Lip Map"); }
    virtual FColor GetTypeColor() const override { return FColor::Red; }
    virtual UClass* GetSupportedClass() const override { return UHSFLipMap::StaticClass(); }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};


class FAssetTypeActions_HSFLipSyncDataPack : public FAssetTypeActions_Base {
public:
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_HSFLipSyncDataPack", "HSF Lip Sync Data Pack"); }
    virtual FColor GetTypeColor() const override { return FColor::Red; }
    virtual UClass* GetSupportedClass() const override { return UHSFLipSyncDataPack::StaticClass(); }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};