#pragma once
#include "CoreMinimal.h"
#include "SQEX_BonamikChangingParameter_v2.h"
#include "SQEX_BonamikChangingParameterExt_v2.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikChangingParameterExt_v2 : public FSQEX_BonamikChangingParameter_v2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_ValueExt;
    
    BONAMIKRT_API FSQEX_BonamikChangingParameterExt_v2();
};

