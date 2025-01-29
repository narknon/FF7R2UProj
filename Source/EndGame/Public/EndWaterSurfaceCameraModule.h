#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndWaterSurfaceCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndWaterSurfaceCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndWaterSurfaceCameraModule();
};

