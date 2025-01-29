#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCompareLocationType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCompareLocationType : uint8 {
    Nearest,
    Farest,
};

