#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndHoldObjectCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndHoldObjectCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndHoldObjectCameraModule();
};

