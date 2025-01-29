#pragma once
#include "CoreMinimal.h"
#include "EEndBattleReactionInfluenceType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleReactionInfluenceType : uint8 {
    RadiusInfinite,
    RadiusShort,
    RadiusMiddle,
    RadiusLong,
    MoveSpeed,
    None = 100,
};

