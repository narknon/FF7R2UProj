#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableGambitFortIconPriority.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableGambitFortIconPriority : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Priority;
    
public:
    ENDDATAOBJECT_API FEndDataTableGambitFortIconPriority();
};

