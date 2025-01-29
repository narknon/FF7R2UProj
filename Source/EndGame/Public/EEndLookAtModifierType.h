#pragma once
#include "CoreMinimal.h"
#include "EEndLookAtModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndLookAtModifierType : uint8 {
    None,
    ForceDisableLookAt,
    AutoDisableLookAt,
    ForceEnableLookAt,
    HeadOnly,
    MeshSpace,
    UseUpAxis,
    LookAway,
    Max,
};

