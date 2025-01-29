#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SQEXSEADAnimNotifyPlayAutoSeParams.h"
#include "SQEXSEADAnimNotifyState_PlayAutoSe.generated.h"

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class SQEXSEAD_API USQEXSEADAnimNotifyState_PlayAutoSe : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSQEXSEADAnimNotifyPlayAutoSeParams PlaySettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FadeOutDuration;
    
    USQEXSEADAnimNotifyState_PlayAutoSe();

};

