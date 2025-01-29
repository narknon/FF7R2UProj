#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDestructionActionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDestructionActionType : uint8 {
    None,
    Add,
    Destruction,
};

