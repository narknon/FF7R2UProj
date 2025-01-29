#pragma once
#include "CoreMinimal.h"
#include "EEndPlayRateModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndPlayRateModifierType : uint8 {
    Field,
    Battle,
    CharaSpec,
    Notify,
    WildAnimal,
    Dialogue,
    Debug,
};

