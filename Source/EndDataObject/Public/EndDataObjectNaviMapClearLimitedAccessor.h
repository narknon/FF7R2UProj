#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectAccessorBase.h"
#include "EndDataObjectNaviMapClearLimitedAccessor.generated.h"

USTRUCT(BlueprintType)
struct ENDDATAOBJECT_API FEndDataObjectNaviMapClearLimitedAccessor : public FEndDataObjectAccessorBase {
    GENERATED_BODY()
public:
    FEndDataObjectNaviMapClearLimitedAccessor();
};

