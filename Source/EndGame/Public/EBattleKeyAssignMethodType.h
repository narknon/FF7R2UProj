#pragma once
#include "CoreMinimal.h"
#include "EBattleKeyAssignMethodType.generated.h"

UENUM(BlueprintType)
enum class EBattleKeyAssignMethodType : uint8 {
    None = 255,
    Normal = 0,
    Down,
    Dodge,
};

