#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateConnectEncount.generated.h"

UENUM(BlueprintType)
enum class EEndExtensionAIStateConnectEncount : uint8 {
    NONE,
    PLAYER_CAUTION,
    ENEMY_CAUTION,
    ENEMY_RETURN_HOME,
    FRIEND_CAUTION,
    ENEMY_HYBRID_CAUTION,
    ENEMY_HYBRID_RETURN_HOME,
};

