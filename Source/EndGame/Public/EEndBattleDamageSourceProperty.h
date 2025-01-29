#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDamageSourceProperty.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDamageSourceProperty : uint8 {
    PhysicsNear,
    Magic,
    PhysicsFar,
    MAX,
};

