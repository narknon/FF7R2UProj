#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectAccessorBase.h"
#include "EndDataObjectInitPartySetDataAccessor.generated.h"

USTRUCT(BlueprintType)
struct ENDDATAOBJECT_API FEndDataObjectInitPartySetDataAccessor : public FEndDataObjectAccessorBase {
    GENERATED_BODY()
public:
    FEndDataObjectInitPartySetDataAccessor();
};

