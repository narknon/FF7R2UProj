#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCommandCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndCommandCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndCommandCameraModule();
};

