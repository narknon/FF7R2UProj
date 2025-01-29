#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndLifeSpotInputCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndLifeSpotInputCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndLifeSpotInputCameraModule();
};

