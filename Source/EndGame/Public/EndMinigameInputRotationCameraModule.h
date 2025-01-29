#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndMinigameInputRotationCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndMinigameInputRotationCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndMinigameInputRotationCameraModule();
};

