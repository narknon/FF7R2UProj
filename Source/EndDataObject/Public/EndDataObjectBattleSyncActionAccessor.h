#pragma once
#include "CoreMinimal.h"
#include "EndDataObjectAccessorBase.h"
#include "EndDataObjectBattleSyncActionAccessor.generated.h"

USTRUCT(BlueprintType)
struct ENDDATAOBJECT_API FEndDataObjectBattleSyncActionAccessor : public FEndDataObjectAccessorBase {
    GENERATED_BODY()
public:
    FEndDataObjectBattleSyncActionAccessor();
};

