#pragma once
#include "CoreMinimal.h"
#include "EEndAIState.generated.h"

UENUM(BlueprintType)
enum class EEndAIState : uint8 {
    EMPTY,
    DO_NOTHINY,
    CONNECT_ENCOUNT,
    BATTLE,
    STAY,
    MOVE_TO,
    LEAD,
    FOLLOW,
    WANDERING,
    ANIMATION,
    SINGLE_ANIMATION,
    UNIQUE,
    INTEREST,
    WILD_ANIMAL,
    BATTLE_EVACUATION,
    HINT_ANIMAL,
    FIELDACTION,
    MAX,
};

