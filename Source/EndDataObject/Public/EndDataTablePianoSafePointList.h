#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePianoSafePointList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePianoSafePointList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPoint_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTablePianoSafePointList();
};

