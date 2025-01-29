#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableVehicleTargetIconInterruptGetOff.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableVehicleTargetIconInterruptGetOff : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ObjectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
public:
    ENDDATAOBJECT_API FEndDataTableVehicleTargetIconInterruptGetOff();
};

