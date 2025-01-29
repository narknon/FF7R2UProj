#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCaitSithVentMoveCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndCaitSithVentMoveCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndCaitSithVentMoveCameraModule();
};

