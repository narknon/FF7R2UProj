#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSecondaryCharacterCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndSecondaryCharacterCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSecondaryCharacterCameraModule();
};

