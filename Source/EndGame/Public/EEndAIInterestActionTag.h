#pragma once
#include "CoreMinimal.h"
#include "EEndAIInterestActionTag.generated.h"

UENUM(BlueprintType)
enum class EEndAIInterestActionTag : uint8 {
    Move,
    LookAt,
    Saccade,
    BodyEmotion,
    BodyControl,
    Voice,
    Max,
};

