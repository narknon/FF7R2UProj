#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAttackDirectionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAttackDirectionType : uint8 {
    Front,
    Right,
    Left,
    Special,
};

