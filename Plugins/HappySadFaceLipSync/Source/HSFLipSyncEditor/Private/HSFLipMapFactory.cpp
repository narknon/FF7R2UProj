#include "HSFLipMapFactory.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "UHSFLipMap_Factory"

UHSFLipMapFactory::UHSFLipMapFactory() {
    bCreateNew = true;           
    bEditAfterNew = true;       
	bEditorImport = true;
    SupportedClass = UHSFLipMap::StaticClass();
}

UObject* UHSFLipMapFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) {
    return NewObject<UHSFLipMap>(InParent, Class, Name, Flags);
}

FText UHSFLipMapFactory::GetDisplayName() const
{
	return LOCTEXT("DisplayName", "HSF Lip Map");
}

static bool bSoundFactorySuppressImportOverwriteDialog = false;

uint32 UHSFLipMapFactory::GetMenuCategories() const
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	return AssetTools.RegisterAdvancedAssetCategory("HappySadFace", LOCTEXT("AssetCategoryName", "HappySadFace"));
}



bool UHSFLipMapFactory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UHSFLipMapFactory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	FString PackagePath = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());

	UHSFLipMap* ImportedAsset = NewObject<UHSFLipMap>(InParent, Name, Flags);
	FString FilePath = FPaths::GetPath(CurrentFilename);
	FPaths::MakePathRelativeTo(FilePath, *FPaths::ProjectDir());
	return ImportedAsset;
}
#undef  LOCTEXT_NAMESPACE