#pragma once
#include "CoreMinimal.h"
#include "ECollisionAndNavProfileType.generated.h"

UENUM(BlueprintType)
enum class ECollisionAndNavProfileType : uint8 {
    Wall,
    Speacial_Wall,
    NoCollision,
    Max,
};

