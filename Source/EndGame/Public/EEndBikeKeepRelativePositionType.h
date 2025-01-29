#pragma once
#include "CoreMinimal.h"
#include "EEndBikeKeepRelativePositionType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeKeepRelativePositionType : uint8 {
    None,
    DirectValue,
    EntryPosition,
};

