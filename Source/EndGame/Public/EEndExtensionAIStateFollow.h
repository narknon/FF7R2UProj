#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateFollow.generated.h"

UENUM(BlueprintType)
enum class EEndExtensionAIStateFollow : uint8 {
    NONE,
    PLAYER,
    PLAYER_SUB,
    CHOCOBO,
    CHOCOBO_MEMBER,
    CHOCOBO_MEMBER_SKY,
    CHOCOBO_MEMBER_OCEAN,
    CHOCOBO_SUB,
    CHOCOBO_ROPE,
    HINA_CHOCOBO,
    STALKER,
    STOP_AND_WALK,
    DATE,
};

