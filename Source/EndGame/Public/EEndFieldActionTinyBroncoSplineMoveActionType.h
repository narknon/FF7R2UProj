#pragma once
#include "CoreMinimal.h"
#include "EEndFieldActionTinyBroncoSplineMoveActionType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldActionTinyBroncoSplineMoveActionType : uint8 {
    StableMove,
    UnStableMove,
    ForceMoveOnce,
};

