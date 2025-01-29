#pragma once
#include "CoreMinimal.h"
#include "ECommandType.generated.h"

UENUM(BlueprintType)
enum class ECommandType : uint8 {
    ECommandType_ABILITY,
    ECommandType_MAGIC,
    ECommandType_LIMIT,
    ECommandType_SUMMON,
    ECommandType_ITEM,
    ECommandType_COMBINATION,
};

