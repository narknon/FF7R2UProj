#pragma once
#include "CoreMinimal.h"
#include "EEndBattleEasySpawnEnableRagdollType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleEasySpawnEnableRagdollType : uint8 {
    Deaded,
    Spawned,
    MovedToSocket,
    None,
};

