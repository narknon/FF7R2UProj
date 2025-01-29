#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDamageSourceDisableBackgroundType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDamageSourceDisableBackgroundType : uint8 {
    All,
    NoHit,
    WallOnly,
    TerrainOnly,
    AllWithCharaWall,
};

