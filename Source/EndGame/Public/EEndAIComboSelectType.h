#pragma once
#include "CoreMinimal.h"
#include "EEndAIComboSelectType.generated.h"

UENUM(BlueprintType)
enum class EEndAIComboSelectType : uint8 {
    Sequence,
    Random,
    Lot,
};

