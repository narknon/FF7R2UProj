#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCharacterAdjustCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCharacterAdjustCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    FEndCharacterAdjustCameraModule();
};

