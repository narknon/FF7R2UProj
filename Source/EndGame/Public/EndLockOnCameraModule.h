#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndLockOnCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndLockOnCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndLockOnCameraModule();
};

