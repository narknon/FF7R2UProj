#pragma once
#include "CoreMinimal.h"
#include "EndHeliLookAtType.generated.h"

UENUM(BlueprintType)
enum class EndHeliLookAtType : uint8 {
    MoveDirection,
    SequencerData,
    MAX,
};

