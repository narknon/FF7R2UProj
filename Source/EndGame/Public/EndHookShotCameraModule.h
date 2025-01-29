#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndHookShotCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndHookShotCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndHookShotCameraModule();
};

