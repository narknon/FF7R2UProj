#pragma once
#include "CoreMinimal.h"
#include "EEndCollisionFilterMask.generated.h"

UENUM(BlueprintType)
enum class EEndCollisionFilterMask : uint8 {
    EEndCollisionFilterMask_None,
    EEndCollisionFilterMask_PhysicsStaticMesh,
    EEndCollisionFilterMask_SimulatingPhysics,
};

