#pragma once
#include "CoreMinimal.h"
#include "EEndGravityLayer.generated.h"

UENUM(BlueprintType)
enum class EEndGravityLayer : uint8 {
    Low,
    Jump,
    Animation,
    Battle,
    Debug,
    Max,
};

