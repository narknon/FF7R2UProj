#pragma once
#include "CoreMinimal.h"
#include "EEndBattleTargetCorrectionDistanceType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleTargetCorrectionDistanceType : uint8 {
    TargetPosition,
    TargetBackwardLinePosition,
    FieldPosition,
    FieldPositionScaleRoot,
    JustMoveToFieldPosition,
};

