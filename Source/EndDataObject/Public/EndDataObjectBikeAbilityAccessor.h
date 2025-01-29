#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectAccessorBase.h"
#include "EndDataObjectBikeAbilityAccessor.generated.h"

USTRUCT(BlueprintType)
struct ENDDATAOBJECT_API FEndDataObjectBikeAbilityAccessor : public FEndDataObjectAccessorBase {
    GENERATED_BODY()
public:
    FEndDataObjectBikeAbilityAccessor();
};

