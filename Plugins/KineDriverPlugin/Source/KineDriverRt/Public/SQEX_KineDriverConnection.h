#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_ConnectionType.h"
#include "SQEX_KineDriverPortInfo.h"
#include "SQEX_KineDriverConnection.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverConnection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESQEX_KD_ConnectionType ConnectionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_KineDriverPortInfo InPortInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEX_KineDriverPortInfo OutPortInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OtherSourceParamIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 OtherTargetParamIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Coef;
    
    KINEDRIVERRT_API FSQEX_KineDriverConnection();
};

