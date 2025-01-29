#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ESQEX_KD_MirrorAcrossType.h"
#include "SQEX_KineDriverMirrorParams.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverMirrorParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnableMirroring;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FQuat MirrorSourceQuaternion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FQuat MirrorDestinationQuaternion;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESQEX_KD_MirrorAcrossType MirrorAcross;
    
    KINEDRIVERRT_API FSQEX_KineDriverMirrorParams();
};

