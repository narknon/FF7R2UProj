#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndDoorCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndDoorCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndDoorCameraModule();
};

