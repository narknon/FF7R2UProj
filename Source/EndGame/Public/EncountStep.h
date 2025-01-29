#pragma once
#include "CoreMinimal.h"
#include "EncountStep.generated.h"

UENUM(BlueprintType)
enum class EncountStep : uint8 {
    ActorPopWait,
    ReadyEncount,
    EncountEnd,
    Finish,
    Remove,
    StepMax,
};

