#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionDefinition.generated.h"

UENUM(BlueprintType)
enum class EEndAIActionDefinition : uint8 {
    Empty,
    Field_Wandering,
    Field_Fixed,
    Move,
    MoveSequence,
    Ability,
    Animation,
    Trans,
    Combo,
    ComboConnect,
    Guard,
    Combination,
    CombinationAbility,
    ReactionAvoid,
    DoNothing,
    Max,
};

