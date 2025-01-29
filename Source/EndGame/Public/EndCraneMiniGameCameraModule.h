#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCraneMiniGameCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCraneMiniGameCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    FEndCraneMiniGameCameraModule();
};

