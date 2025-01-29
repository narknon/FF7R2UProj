#pragma once
#include "CoreMinimal.h"
#include "EndVehicleCameraModule.h"
#include "EndDolphinSwimCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDolphinSwimCameraModule : public FEndVehicleCameraModule {
    GENERATED_BODY()
public:
    FEndDolphinSwimCameraModule();
};

