#pragma once
#include "CoreMinimal.h"
#include "EModifierVolumeType.generated.h"

UENUM(BlueprintType)
namespace EModifierVolumeType {
    enum Type {
        CoverPc,
        CoverEnemy,
        Cover,
        WhiteList,
        BlackList,
        Defence,
        Path,
        AirPoint,
        Chase,
        Wall,
        Ceil,
        Water,
        TargetLocation,
        Decoy,
        PopPoint,
        Overlap,
        FlyThrough,
        Ignore,
    };
}

