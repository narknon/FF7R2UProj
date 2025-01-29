#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndVehicleSplineMoveCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleSplineMoveCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndVehicleSplineMoveCameraModule();
};

