#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SQEX_KineDriver_AnimNotify_Enable.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class KBDRT_API USQEX_KineDriver_AnimNotify_Enable : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_Enable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_Label;
    
    USQEX_KineDriver_AnimNotify_Enable();

};

