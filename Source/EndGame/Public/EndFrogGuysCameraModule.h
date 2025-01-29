#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndFrogGuysCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndFrogGuysCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndFrogGuysCameraModule();
};

