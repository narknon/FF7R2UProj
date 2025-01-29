#pragma once
#include "CoreMinimal.h"
#include "EEndVehicleSeControlTypes.generated.h"

UENUM(BlueprintType)
namespace EEndVehicleSeControlTypes {
    enum Type {
        Field,
        GBike,
        BuggyShooting,
        Cut,
        MAX,
    };
}

