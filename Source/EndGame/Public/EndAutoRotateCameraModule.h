#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndAutoRotateCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndAutoRotateCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndAutoRotateCameraModule();
};

