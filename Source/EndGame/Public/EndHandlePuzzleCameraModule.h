#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndHandlePuzzleCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndHandlePuzzleCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndHandlePuzzleCameraModule();
};

