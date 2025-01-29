#pragma once
#include "CoreMinimal.h"
#include "AlphaBlend.h"
#include "EndDialogueSequenceBlendInSetting.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDialogueSequenceBlendInSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendingWaitTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAlphaBlendOption BlendOption;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CharacterSmoothingBlendTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAlphaBlendOption CharacterSmoothingBlendOption;
    
    FEndDialogueSequenceBlendInSetting();
};

