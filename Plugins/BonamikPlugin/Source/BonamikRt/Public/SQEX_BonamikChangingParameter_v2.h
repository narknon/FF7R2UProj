#pragma once
#include "CoreMinimal.h"
#include "ESQEX_Bonamik_Parameters.h"
#include "SQEX_BonamikChangingParameter_v2.generated.h"

USTRUCT(BlueprintType)
struct FSQEX_BonamikChangingParameter_v2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> m_Groups;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEX_Bonamik_Parameters> m_Parameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Value;
    
    BONAMIKRT_API FSQEX_BonamikChangingParameter_v2();
};

