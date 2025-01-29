#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EMotionPhaseNotify.h"
#include "EndAnimNotifyLifeStreamInjection.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyLifeStreamInjection : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EMotionPhaseNotify MotionNotify;
    
    UEndAnimNotifyLifeStreamInjection();

};

