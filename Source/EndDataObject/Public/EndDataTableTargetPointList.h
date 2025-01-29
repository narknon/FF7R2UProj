#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableTargetPointList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableTargetPointList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPointList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableTargetPointList();
};

