#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_AnimNotify_Bonamik_ResetAndPreRoll.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_AnimNotify_Bonamik_ResetAndPreRoll : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_Reset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 m_PreRoll;
    
    USQEX_AnimNotify_Bonamik_ResetAndPreRoll();

};

