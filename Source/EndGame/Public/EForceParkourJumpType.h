#pragma once
#include "CoreMinimal.h"
#include "EForceParkourJumpType.generated.h"

UENUM(BlueprintType)
enum class EForceParkourJumpType : uint8 {
    Default,
    Jump,
    Step,
    VaultMin,
    VaultMiddle,
    VaultMax,
    SuperHighJump,
    SuperFall,
    Jump_DisableRotationControl,
    WaterFall,
    Fence,
    MAX,
};

