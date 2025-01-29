#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndClimbingActionCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndClimbingActionCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndClimbingActionCameraModule();
};

