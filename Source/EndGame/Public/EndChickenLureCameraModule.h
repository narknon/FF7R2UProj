#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndChickenLureCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndChickenLureCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndChickenLureCameraModule();
};

