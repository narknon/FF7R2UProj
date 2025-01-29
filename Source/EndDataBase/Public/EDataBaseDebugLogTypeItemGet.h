#pragma once
#include "CoreMinimal.h"
#include "EDataBaseDebugLogTypeItemGet.generated.h"

UENUM(BlueprintType)
enum class EDataBaseDebugLogTypeItemGet : uint8 {
    NONE,
    ENEMY_KILL,
    SHOP,
    TRESURE,
    REWARD,
};

