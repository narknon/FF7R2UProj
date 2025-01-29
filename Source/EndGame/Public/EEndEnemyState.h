#pragma once
#include "CoreMinimal.h"
#include "EEndEnemyState.generated.h"

UENUM(BlueprintType)
enum class EEndEnemyState : uint8 {
    None,
    Hidden,
    Alive,
    Defeated,
    Dead,
};

