#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboParkingPoint.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboParkingPoint : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ChocoboParkingPointName_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboParkingPoint();
};

