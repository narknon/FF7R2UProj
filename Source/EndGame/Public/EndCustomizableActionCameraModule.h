#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndCustomizableActionCameraModule.generated.h"

USTRUCT(BlueprintType)
struct FEndCustomizableActionCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndCustomizableActionCameraModule();
};

