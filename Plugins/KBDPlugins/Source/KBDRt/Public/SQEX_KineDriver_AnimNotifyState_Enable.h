#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SQEX_KineDriver_AnimNotifyState_Enable.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class KBDRT_API USQEX_KineDriver_AnimNotifyState_Enable : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_Enable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_Label;
    
    USQEX_KineDriver_AnimNotifyState_Enable();

};

