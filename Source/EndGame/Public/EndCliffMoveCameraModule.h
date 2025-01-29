#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCliffMoveCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndCliffMoveCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndCliffMoveCameraModule();
};

