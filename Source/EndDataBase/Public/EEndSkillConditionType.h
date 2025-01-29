#pragma once
#include "CoreMinimal.h"
#include "EEndSkillConditionType.generated.h"

UENUM(BlueprintType)
enum class EEndSkillConditionType : uint8 {
    None,
    HPUnder,
    HPOver,
    MPUnder,
    MPOver,
    Danger,
};

