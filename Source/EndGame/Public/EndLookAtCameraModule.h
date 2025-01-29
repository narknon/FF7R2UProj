#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndLookAtCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndLookAtCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndLookAtCameraModule();
};

