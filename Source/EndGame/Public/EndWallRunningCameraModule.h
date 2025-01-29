#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndWallRunningCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndWallRunningCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndWallRunningCameraModule();
};

