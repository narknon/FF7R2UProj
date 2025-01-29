#pragma once
#include "CoreMinimal.h"
#include "EEndCameraLadderStateType.generated.h"

UENUM(BlueprintType)
enum class EEndCameraLadderStateType : uint8 {
    Enter,
    Move,
    Leave,
    MAX,
};

