#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndAdjustLengthBattleCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndAdjustLengthBattleCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndAdjustLengthBattleCameraModule();
};

