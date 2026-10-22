#include "EndSkeletonCompatDataObjectFactory.h"

#include "AssetTypeCategories.h"
#include "EndSkeletonCompatDataObject.h"

UEndSkeletonCompatDataObjectFactory::UEndSkeletonCompatDataObjectFactory()
{
	SupportedClass = UEndSkeletonCompatDataObject::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UEndSkeletonCompatDataObjectFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UEndSkeletonCompatDataObject>(InParent, InClass, InName, Flags | RF_Transactional);
}

uint32 UEndSkeletonCompatDataObjectFactory::GetMenuCategories() const
{
	return EAssetTypeCategories::Animation;
}

FText UEndSkeletonCompatDataObjectFactory::GetDisplayName() const
{
	return NSLOCTEXT("RebirthSkelCompat", "FactoryName", "Skeleton Compatibility Data Object");
}

FString UEndSkeletonCompatDataObjectFactory::GetDefaultNewAssetName() const
{
	return TEXT("DO_SkeletonCompat");
}
