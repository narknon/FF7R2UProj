#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ESQEX_KD_ExtrapolateType.h"
#include "SQEX_KineDriverCurveKey.h"
#include "SQEX_KineDriverEffectorLinkWith.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_KineDriverEffectorLinkWith {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_KD_ExtrapolateType> ExtrapType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSQEX_KineDriverCurveKey> Keys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector4> aSegmentVec;
    
    KINEDRIVERRT_API FSQEX_KineDriverEffectorLinkWith();
};

