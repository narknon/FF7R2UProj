#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_ParameterType.h"
#include "SQEX_KineDriverPortInfo.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverPortInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString NodeName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OperatorIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_KD_ParameterType> ParameterType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 MultiIndex;
    
    KINEDRIVERRT_API FSQEX_KineDriverPortInfo();
};

