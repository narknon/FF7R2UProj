#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableUniqueActionRCSMove.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableUniqueActionRCSMove : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> StateChangeID_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> Rate_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableUniqueActionRCSMove();
};

