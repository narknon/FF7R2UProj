#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSwimCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndSwimCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSwimCameraModule();
};

