#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSimpleLeaderChangeCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndSimpleLeaderChangeCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSimpleLeaderChangeCameraModule();
};

