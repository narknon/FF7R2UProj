#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDeadDirectionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDeadDirectionType : uint8 {
    None,
    LifeStream,
    Explosion,
    DarkEmission,
    Purification,
    BlackSmoke,
    WhiteSmoke,
    Digital,
    Gizoku,
    Petrify,
    FeelerNormal = 50,
    FeelerSpecial,
    PraecoMiniNormal,
    PraecoMiniFinish,
};

