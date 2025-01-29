#pragma once
#include "CoreMinimal.h"
#include "EEndActorTickPhase.generated.h"

UENUM(BlueprintType)
enum class EEndActorTickPhase : uint8 {
    None,
    TickMovementAndAniamation,
    EvalAnimation,
    TickActor,
    EvalPostAnimation,
};

