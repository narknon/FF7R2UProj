#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAttributeType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAttributeType : uint8 {
    Fire,
    Ice,
    Thunder,
    Wind,
    Max,
    None = Max,
};

