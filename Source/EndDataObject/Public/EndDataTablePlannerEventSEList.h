#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlannerEventSEList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlannerEventSEList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Value;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlannerEventSEList();
};

