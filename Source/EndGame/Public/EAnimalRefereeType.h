#pragma once
#include "CoreMinimal.h"
#include "EAnimalRefereeType.generated.h"

UENUM(BlueprintType)
enum class EAnimalRefereeType : uint8 {
    Rank,
    Score,
    Max,
};

