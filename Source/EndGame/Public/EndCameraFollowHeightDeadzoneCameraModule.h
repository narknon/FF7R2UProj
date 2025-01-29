#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCameraFollowHeightDeadzoneCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCameraFollowHeightDeadzoneCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    FEndCameraFollowHeightDeadzoneCameraModule();
};

