#pragma once
#include "CoreMinimal.h"
#include "EEndDialogueSequenceSpotLight.generated.h"

UENUM(BlueprintType)
enum class EEndDialogueSequenceSpotLight : uint8 {
    KeyLight,
    FillLight,
    BackLight,
    EyeLight,
    Max,
};

