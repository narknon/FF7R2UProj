#pragma once
#include "CoreMinimal.h"
#include "EEndVehicleRoadAttributeTypes.generated.h"

UENUM(BlueprintType)
namespace EEndVehicleRoadAttributeTypes {
    enum Type {
        Default,
        Con_Clean,
        Con_Sandy,
        Sandy,
        Grass,
        Muddy,
        Water,
        MAX,
    };
}

