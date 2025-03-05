#include "HSFLipSyncDataPackFactory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "UHSFLipSyncDataPack_Factory"

UHSFLipSyncDataPackFactory::UHSFLipSyncDataPackFactory() {
    bCreateNew = true;           
    bEditAfterNew = true;        
    bEditorImport = true;
    SupportedClass = UHSFLipSyncDataPack::StaticClass();
}

UObject* UHSFLipSyncDataPackFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
    return NewObject<UHSFLipSyncDataPack>(InParent, Class, Name, Flags);
}

FText UHSFLipSyncDataPackFactory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "HSF Lip Sync Data Pack");
}

uint32 UHSFLipSyncDataPackFactory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("HappySadFace", LOCTEXT("AssetCategoryName", "HappySadFace"));
}



bool UHSFLipSyncDataPackFactory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UHSFLipSyncDataPackFactory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UHSFLipSyncDataPack* ImportedAsset = NewObject<UHSFLipSyncDataPack>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}
#undef  LOCTEXT_NAMESPACE