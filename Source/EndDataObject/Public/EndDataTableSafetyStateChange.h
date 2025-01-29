#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableSafetyStateChange.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableSafetyStateChange : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AssignStateChangeID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableSafetyStateChange();
};

