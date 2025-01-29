#pragma once
#include "CoreMinimal.h"
#include "AlphaBlend.h"
#include "EndDialogueSequenceBlendOutSetting.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueSequenceBlendOutSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendStartTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAlphaBlendOption BlendOption;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSetFieldCameraDirection;
    
    FEndDialogueSequenceBlendOutSetting();
};

