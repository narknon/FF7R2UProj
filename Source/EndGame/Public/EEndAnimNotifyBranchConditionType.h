#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBranchConditionType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyBranchConditionType : uint8 {
    None,
    CharaID,
    Weapon1CharaID,
    Weapon2CharaID,
    Weapon3CharaID,
    Weapon4CharaID,
    AbilityID,
};

