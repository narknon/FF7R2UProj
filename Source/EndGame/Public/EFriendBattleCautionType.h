#pragma once
#include "CoreMinimal.h"
#include "EFriendBattleCautionType.generated.h"

UENUM(BlueprintType)
enum class EFriendBattleCautionType : uint8 {
    KeepMoving,
    MoveThenWait,
    BackAndForth,
    Formation,
    MAX,
};

