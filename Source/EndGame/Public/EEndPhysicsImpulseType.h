#pragma once
#include "CoreMinimal.h"
#include "EEndPhysicsImpulseType.generated.h"

UENUM()
enum class EEndPhysicsImpulseType : int32 {
    Default,
    Angular,
    Radial,
};

