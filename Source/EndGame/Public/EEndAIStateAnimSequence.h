#pragma once
#include "CoreMinimal.h"
#include "EEndAIStateAnimSequence.generated.h"

UENUM(BlueprintType)
enum class EEndAIStateAnimSequence : uint8 {
    Start,
    Loop,
    End,
    Max,
    None,
};

