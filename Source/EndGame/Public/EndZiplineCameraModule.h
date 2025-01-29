#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndZiplineCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndZiplineCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndZiplineCameraModule();
};

