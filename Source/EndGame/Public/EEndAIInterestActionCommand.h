#pragma once
#include "CoreMinimal.h"
#include "EEndAIInterestActionCommand.generated.h"

UENUM(BlueprintType)
enum class EEndAIInterestActionCommand : uint8 {
    Approach,
    PlayAnimation,
    OverrideAnim,
    Escape,
    Wait,
    LookAt,
    OverrideAnimEnd,
    LookAtEnd,
    UpperBodyBlendAnimation,
    UpperBodyBlendAnimationEnd,
    Emotion,
    EmotionEnd,
    OverrideIdleVariation,
    Turn,
    TurnEnd,
    AIStateGroup,
    None,
    Max,
};

