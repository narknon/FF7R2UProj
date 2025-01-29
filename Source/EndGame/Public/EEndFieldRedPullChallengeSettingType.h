#pragma once
#include "CoreMinimal.h"
#include "EEndFieldRedPullChallengeSettingType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldRedPullChallengeSettingType : uint8 {
    Normal,
    Random,
    MAX,
};

