#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndRopeCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndRopeCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndRopeCameraModule();
};

