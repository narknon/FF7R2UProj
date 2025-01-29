#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndHookRopeCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndHookRopeCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndHookRopeCameraModule();
};

