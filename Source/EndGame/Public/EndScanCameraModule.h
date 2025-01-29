#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndScanCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndScanCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndScanCameraModule();
};

