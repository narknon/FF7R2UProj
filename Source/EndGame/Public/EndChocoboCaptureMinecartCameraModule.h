#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndChocoboCaptureMinecartCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboCaptureMinecartCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndChocoboCaptureMinecartCameraModule();
};

