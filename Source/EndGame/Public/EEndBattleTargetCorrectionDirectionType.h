#pragma once
#include "CoreMinimal.h"
#include "EEndBattleTargetCorrectionDirectionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleTargetCorrectionDirectionType : uint8 {
    TargetPosition,
    TargetBackward,
    FieldPosition,
};

