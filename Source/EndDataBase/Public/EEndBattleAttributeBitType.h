#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAttributeBitType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAttributeBitType : uint8 {
    None,
    Fire,
    Ice,
    Thunder = 4,
    Wind = 8,
};

