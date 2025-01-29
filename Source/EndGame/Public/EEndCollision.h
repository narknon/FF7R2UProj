#pragma once
#include "CoreMinimal.h"
#include "EEndCollision.generated.h"

UENUM(BlueprintType)
namespace EEndCollision {
    enum Type {
        SPHERE,
        CAPSULE,
        BOX,
        CONVEX,
        MAX,
    };
}

