#pragma once
#include "CoreMinimal.h"
#include "EEndAIAbilityDefinition.generated.h"

UENUM(BlueprintType)
enum class EEndAIAbilityDefinition : uint8 {
    Normal,
    ParallelMove,
    Counter,
    Special,
    Combination,
    ComboFirstDummy,
    WaveAttackLeader,
    Max,
};

