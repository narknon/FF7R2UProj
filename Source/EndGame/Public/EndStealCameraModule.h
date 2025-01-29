#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndStealCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndStealCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndStealCameraModule();
};

