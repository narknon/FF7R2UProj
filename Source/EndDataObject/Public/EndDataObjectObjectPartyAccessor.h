#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectAccessorBase.h"
#include "EndDataObjectObjectPartyAccessor.generated.h"

USTRUCT(BlueprintType)
struct ENDDATAOBJECT_API FEndDataObjectObjectPartyAccessor : public FEndDataObjectAccessorBase {
    GENERATED_BODY()
public:
    FEndDataObjectObjectPartyAccessor();
};

