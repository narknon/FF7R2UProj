#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EChocoboCaptureRodeoPhase.h"
#include "EEndHandType.h"
#include "EndAnimNotifyChocoboCaptureRodeo.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class ENDGAME_API UEndAnimNotifyChocoboCaptureRodeo : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EChocoboCaptureRodeoPhase PhaseNotify;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AttachInterpSec;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndHandType HandType;
    
    UEndAnimNotifyChocoboCaptureRodeo();

};

