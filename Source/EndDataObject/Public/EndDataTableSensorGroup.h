#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableSensorGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableSensorGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> IsSensorTypeAvailable_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableSensorGroup();
};

