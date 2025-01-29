#pragma once
#include "CoreMinimal.h"
#include "EEndBumpActionLayer.generated.h"

UENUM(BlueprintType)
enum class EEndBumpActionLayer : uint8 {
    Action,
    Field,
    Animation,
    UpperAnimation,
    Notify,
    ComponentField,
    AI,
    Vehicle,
    Movement,
    Debug,
    Max,
};

