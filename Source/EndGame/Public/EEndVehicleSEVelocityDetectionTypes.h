#pragma once
#include "CoreMinimal.h"
#include "EEndVehicleSEVelocityDetectionTypes.generated.h"

UENUM(BlueprintType)
namespace EEndVehicleSEVelocityDetectionTypes {
    enum Type {
        EndCharaMovedVelocity,
        OwnerVelocity,
        MeshComponentVelocity,
        CalculateFromMeshLocation,
        EndCharaDesiredVelocity,
        MAX,
    };
}

