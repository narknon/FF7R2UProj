#pragma once
#include "CoreMinimal.h"
#include "EEndMovementRestriction.generated.h"

UENUM(BlueprintType)
enum class EEndMovementRestriction : uint8 {
    None,
    WalkOnlyToDestination,
    ForceWalkToDestination,
    ForceWalkToDestinationAtSameSpeed,
    ForceFinalVectorDestination,
    WalkOrRebelMotion,
    MAX,
};

