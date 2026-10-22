#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EndSkeletonCompatDataObjectFactory.generated.h"

/** Content Browser: Add New > Animation > Skeleton Compatibility Data Object. */
UCLASS(hidecategories = Object)
class UEndSkeletonCompatDataObjectFactory : public UFactory
{
	GENERATED_BODY()

public:
	UEndSkeletonCompatDataObjectFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;
	virtual FString GetDefaultNewAssetName() const override;
};
