#pragma once
#include "CoreMinimal.h"
#include "EEndBattleBreakableRelationActionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleBreakableRelationActionType : uint8 {
    Hidden,
    Visible,
    Replace,
};

