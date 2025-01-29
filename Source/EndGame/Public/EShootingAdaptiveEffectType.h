#pragma once
#include "CoreMinimal.h"
#include "EShootingAdaptiveEffectType.generated.h"

UENUM()
enum class EShootingAdaptiveEffectType : int32 {
    Shot,
    Hit_Endurance,
    Break_Endurance,
    Break_NoEndurance,
    Break_Flip,
    Break_BOSSandSaboten,
    SmallWaves,
    BigWaves,
    Max,
    None,
};

