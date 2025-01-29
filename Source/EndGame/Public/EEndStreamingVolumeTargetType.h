#pragma once
#include "CoreMinimal.h"
#include "EEndStreamingVolumeTargetType.generated.h"

UENUM(BlueprintType)
enum class EEndStreamingVolumeTargetType : uint8 {
    All,
    Editor,
    ROM,
    PS5ROM,
    WinROM,
    HighSpecOnly,
    LowSpecOnly,
};

