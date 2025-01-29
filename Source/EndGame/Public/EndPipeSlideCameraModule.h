#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndPipeSlideCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndPipeSlideCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndPipeSlideCameraModule();
};

