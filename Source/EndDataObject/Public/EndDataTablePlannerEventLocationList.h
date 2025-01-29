#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlannerEventLocationList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlannerEventLocationList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Value;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SequencerValue;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlannerEventLocationList();
};

