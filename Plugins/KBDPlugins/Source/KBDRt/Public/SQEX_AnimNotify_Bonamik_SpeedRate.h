#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_AnimNotify_Bonamik_SpeedRate.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_AnimNotify_Bonamik_SpeedRate : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_SpeedRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float m_Time;
    
    USQEX_AnimNotify_Bonamik_SpeedRate();

};

