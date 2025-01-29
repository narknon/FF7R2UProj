#pragma once
#include "CoreMinimal.h"
#include "EPlayerStatus.generated.h"

UENUM(BlueprintType)
enum class EPlayerStatus : uint8 {
    EPlayerType_NONE,
    EPlayerType_PARTY,
    EPlayerType_GUEST,
    EPlayerType_CACHE,
    EPlayerType_GUEST_Battle,
    EPlayerType_RESERVE,
    EPlayerType_BATTLE_AWAY,
};

