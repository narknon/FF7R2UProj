#pragma once
#include "CoreMinimal.h"
#include "EEndAILayer.generated.h"

UENUM(BlueprintType)
enum class EEndAILayer : uint8 {
    DEFAULT,
    RIDE_MOUNT,
    FIELD_FORCE,
    INTEREST_DEFAULT,
    FIELD_FIELDACTION,
    MINIGAME_LOW,
    VR_OVERRIDE,
    BATTLE_DEFAULT,
    BATTLE_DEMO,
    PV_DEFAULT,
    FIELD_ANIMATION,
    PV_MOVE,
    FIELD_ACTION,
    INTEREST_HIGH,
    SITUATION,
    MINIGAME,
    FIELD_CINEMA,
    CINEMA,
    INTEREST_OVERCINEMA,
    DEBUG,
    MAX,
    EMPTY,
};

