#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikeTalkCondition.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikeTalkCondition : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TriggerSetID_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> Priority_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikeTalkCondition();
};

