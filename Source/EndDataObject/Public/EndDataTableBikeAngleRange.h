#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikeAngleRange.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikeAngleRange : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngleA;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngleB;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikeAngleRange();
};

