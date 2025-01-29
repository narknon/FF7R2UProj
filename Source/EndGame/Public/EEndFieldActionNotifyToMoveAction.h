#pragma once
#include "CoreMinimal.h"
#include "EEndFieldActionNotifyToMoveAction.generated.h"

UENUM(BlueprintType)
enum class EEndFieldActionNotifyToMoveAction : uint8 {
    None,
    Move = 2,
    Attack = 4,
    Parkour = 8,
    Dodge = 16,
    Swimming = 32,
};

