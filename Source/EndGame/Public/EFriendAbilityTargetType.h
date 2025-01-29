#pragma once
#include "CoreMinimal.h"
#include "EFriendAbilityTargetType.generated.h"

UENUM(BlueprintType)
enum class EFriendAbilityTargetType : uint8 {
    None,
    BattleTarget,
    Character,
};

