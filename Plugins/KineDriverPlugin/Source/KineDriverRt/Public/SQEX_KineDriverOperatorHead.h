#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_OperatorType.h"
#include "SQEX_KineDriverOperatorHead.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverOperatorHead {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 WorkIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_KD_OperatorType> OpType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OperatorBody;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Label;
    
    KINEDRIVERRT_API FSQEX_KineDriverOperatorHead();
};

