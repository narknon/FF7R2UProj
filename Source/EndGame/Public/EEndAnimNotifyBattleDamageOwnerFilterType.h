#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBattleDamageOwnerFilterType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyBattleDamageOwnerFilterType : uint8 {
    eALL,
    ePlayer,
    eEnemy,
};

