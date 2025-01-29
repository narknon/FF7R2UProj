#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSpecialResist.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSpecialResist : uint8 {
    Death,
    Morph,
    Petrify,
    Max,
    None = Max,
};

