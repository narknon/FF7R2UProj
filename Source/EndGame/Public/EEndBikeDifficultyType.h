#pragma once
#include "CoreMinimal.h"
#include "EEndBikeDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeDifficultyType : uint8 {
    All,
    Easy,
    Normal,
    Hard,
    Advance,
};

