#pragma once
#include "CoreMinimal.h"
#include "EEndDialogueSequenceEndShotCamera.generated.h"

UENUM(BlueprintType)
enum class EEndDialogueSequenceEndShotCamera : uint8 {
    Cut,
    Unbind,
    Seamless,
};

