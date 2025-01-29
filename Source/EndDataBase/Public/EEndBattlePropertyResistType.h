#pragma once
#include "CoreMinimal.h"
#include "EEndBattlePropertyResistType.generated.h"

UENUM(BlueprintType)
enum class EEndBattlePropertyResistType : uint8 {
    Physics,
    Magic,
    Max,
};

