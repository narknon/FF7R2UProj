#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndControlLiftCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndControlLiftCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    FEndControlLiftCameraModule();
};

