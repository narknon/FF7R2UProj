#pragma once
#include "CoreMinimal.h"
#include "EEndBattleYuffieAttributeBuffType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleYuffieAttributeBuffType : uint8 {
    None,
    Fire,
    Ice,
    Thunder,
    Wind,
    MAX,
};

