#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndForceFeedbackTrack.h"
#include "AnimNotify_EndForceFeedbackAdvanced.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndForceFeedbackAdvanced : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndForceFeedbackTrack Track;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EffectID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWithPriorityControl;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPlayForcibly;
    
    UAnimNotify_EndForceFeedbackAdvanced();

};

