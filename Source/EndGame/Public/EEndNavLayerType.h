#pragma once
#include "CoreMinimal.h"
#include "EEndNavLayerType.generated.h"

UENUM(BlueprintType)
enum class EEndNavLayerType : uint8 {
    Normal,
    Medium,
    OneLarge,
    TwoLarge,
    ThreeLarge,
    FourLarge,
    BattleNormal,
    LayerMax,
};

