#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SQEX_AnimNotifyState_Bonamik_Lerp.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class KBDRT_API USQEX_AnimNotifyState_Bonamik_Lerp : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Lerp;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendOutTime;
    
    USQEX_AnimNotifyState_Bonamik_Lerp();

};

