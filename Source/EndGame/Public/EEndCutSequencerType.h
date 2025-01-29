#pragma once
#include "CoreMinimal.h"
#include "EEndCutSequencerType.generated.h"

UENUM(BlueprintType)
enum class EEndCutSequencerType : uint8 {
    Camera,
    Character,
    Attach,
    Sound,
    Voice,
    Text,
    Effect,
    Light,
    ManualSE,
    CutEvent,
    PlanEvent,
    Root,
    Max,
};

