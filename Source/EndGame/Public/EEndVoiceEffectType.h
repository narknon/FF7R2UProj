#pragma once
#include "CoreMinimal.h"
#include "EEndVoiceEffectType.generated.h"

UENUM(BlueprintType)
enum class EEndVoiceEffectType : uint8 {
    None,
    COM,
    Mask,
};

