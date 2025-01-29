#pragma once
#include "CoreMinimal.h"
#include "EEndDialogueSequenceVersion.generated.h"

UENUM(BlueprintType)
enum class EEndDialogueSequenceVersion : uint8 {
    None,
    FixCommandJump,
    PossessableCamera,
    FixLightGenerator,
    Max,
};

