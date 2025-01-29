#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndVaultCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndVaultCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndVaultCameraModule();
};

