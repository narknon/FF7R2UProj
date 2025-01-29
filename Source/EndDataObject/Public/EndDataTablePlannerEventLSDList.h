#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlannerEventLSDList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlannerEventLSDList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Value;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlannerEventLSDList();
};

