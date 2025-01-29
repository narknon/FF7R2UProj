#pragma once
#include "CoreMinimal.h"
#include "EDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EDifficultyType : uint8 {
    EASY,
    NORMAL,
    HARD,
    ADVANCE,
    MAX,
};

