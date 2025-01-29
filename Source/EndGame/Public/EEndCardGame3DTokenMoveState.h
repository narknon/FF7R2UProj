#pragma once
#include "CoreMinimal.h"
#include "EEndCardGame3DTokenMoveState.generated.h"

UENUM(BlueprintType)
enum class EEndCardGame3DTokenMoveState : uint8 {
    None,
    Moving,
    MoveEnd,
};

