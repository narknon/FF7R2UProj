#pragma once
#include "CoreMinimal.h"
#include "EEndOneShotMoveType.generated.h"

UENUM(BlueprintType)
enum class EEndOneShotMoveType : uint8 {
    Crack,
    Crouch,
    DoorSteps,
    NPCMovePointToPoint,
    Max,
};

