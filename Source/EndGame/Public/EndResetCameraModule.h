#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndResetCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndResetCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndResetCameraModule();
};

