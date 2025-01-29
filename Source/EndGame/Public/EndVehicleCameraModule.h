#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndVehicleCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndVehicleCameraModule();
};

