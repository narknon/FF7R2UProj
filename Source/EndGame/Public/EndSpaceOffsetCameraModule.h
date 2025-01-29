#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSpaceOffsetCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndSpaceOffsetCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSpaceOffsetCameraModule();
};

