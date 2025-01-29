#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableWheelieResetlLocation.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableWheelieResetlLocation : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ResetPoint;
    
public:
    ENDDATAOBJECT_API FEndDataTableWheelieResetlLocation();
};

