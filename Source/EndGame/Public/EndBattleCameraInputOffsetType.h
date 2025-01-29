#pragma once
#include "CoreMinimal.h"
#include "EndBattleCameraInputOffsetType.generated.h"

UENUM(BlueprintType)
enum class EndBattleCameraInputOffsetType : uint8 {
    None,
    Slide,
    Swing,
};

