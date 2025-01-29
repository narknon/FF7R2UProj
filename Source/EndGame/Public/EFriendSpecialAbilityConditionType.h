#pragma once
#include "CoreMinimal.h"
#include "EFriendSpecialAbilityConditionType.generated.h"

UENUM(BlueprintType)
enum class EFriendSpecialAbilityConditionType : uint8 {
    None,
    OnHeat,
    OnBurst,
};

