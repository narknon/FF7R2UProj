#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndLeaderChangeCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndLeaderChangeCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndLeaderChangeCameraModule();
};

