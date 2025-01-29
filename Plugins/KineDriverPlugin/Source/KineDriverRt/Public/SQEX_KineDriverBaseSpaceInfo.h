#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_BaseSpaceType.h"
#include "SQEX_KineDriverBaseSpaceInfo.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverBaseSpaceInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ESQEX_KD_BaseSpaceType BaseSpaceType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BoneName;
    
    KINEDRIVERRT_API FSQEX_KineDriverBaseSpaceInfo();
};

