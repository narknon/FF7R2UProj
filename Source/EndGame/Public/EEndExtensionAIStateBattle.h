#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateBattle.generated.h"

UENUM(BlueprintType)
enum class EEndExtensionAIStateBattle : uint8 {
    NONE,
    PLAYER,
    ENEMY,
    SUB_PLAYER,
    BOSS,
    BOSS_EB0004_MINE,
    BOSS_EB2000,
    FRIEND,
    ENEMY_EN2219,
};

