#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndBuggyAppearCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBuggyAppearCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    FEndBuggyAppearCameraModule();
};

