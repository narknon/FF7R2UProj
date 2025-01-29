#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndIdleHeightStabilizerCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndIdleHeightStabilizerCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndIdleHeightStabilizerCameraModule();
};

