#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlannerEventTalkLocation.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlannerEventTalkLocation : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ConvertLocation;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlannerEventTalkLocation();
};

