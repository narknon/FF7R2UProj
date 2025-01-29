#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndMiniGameBuggyCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndMiniGameBuggyCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndMiniGameBuggyCameraModule();
};

