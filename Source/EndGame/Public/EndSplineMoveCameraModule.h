#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSplineMoveCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndSplineMoveCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSplineMoveCameraModule();
};

