#pragma once
#include "CoreMinimal.h"
#include "ECommandAbilityInfoType.generated.h"

UENUM()
enum class ECommandAbilityInfoType : int32 {
    IsCombinationAbility,
    IsTeleportToExecutor,
    ShouldCheckOcclusion,
};

