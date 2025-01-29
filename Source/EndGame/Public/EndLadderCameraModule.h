#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndLadderCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndLadderCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndLadderCameraModule();
};

