#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndFieldBarretShootingCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldBarretShootingCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndFieldBarretShootingCameraModule();
};

