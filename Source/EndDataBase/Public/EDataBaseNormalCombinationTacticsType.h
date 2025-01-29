#pragma once
#include "CoreMinimal.h"
#include "EDataBaseNormalCombinationTacticsType.generated.h"

UENUM(BlueprintType)
enum class EDataBaseNormalCombinationTacticsType : uint8 {
    Attack,
    Defense,
    Max,
    None = Max,
};

