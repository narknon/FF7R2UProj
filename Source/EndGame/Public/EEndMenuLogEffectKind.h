#pragma once
#include "CoreMinimal.h"
#include "EEndMenuLogEffectKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuLogEffectKind : uint8 {
    None,
    Small,
    Middle,
    Large,
    Weapon,
    Alert,
    Material,
};

