#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndChocoboCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndChocoboCameraModule();
};

