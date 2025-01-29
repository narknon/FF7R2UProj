#pragma once
#include "CoreMinimal.h"
#include "EVfxRaiseTriggerType.generated.h"

UENUM(BlueprintType)
enum class EVfxRaiseTriggerType : uint8 {
    Time,
    KillParticleCount,
};

