#pragma once
#include "CoreMinimal.h"
#include "EEndBattleEnvironmentAnimPlayType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleEnvironmentAnimPlayType : uint8 {
    Play,
    Looping,
    LastFrame,
};

