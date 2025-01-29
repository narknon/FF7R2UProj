#pragma once
#include "CoreMinimal.h"
#include "EEndAIStateBattleEvacuationType.generated.h"

UENUM(BlueprintType)
enum class EEndAIStateBattleEvacuationType : uint8 {
    None,
    Auto,
    FieldMode,
    BattleMode,
};

