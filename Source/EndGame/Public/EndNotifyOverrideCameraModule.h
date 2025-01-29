#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndNotifyOverrideCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndNotifyOverrideCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndNotifyOverrideCameraModule();
};

