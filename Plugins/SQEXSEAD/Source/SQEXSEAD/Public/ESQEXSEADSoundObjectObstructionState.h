#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADSoundObjectObstructionState.generated.h"

UENUM(BlueprintType)
enum class ESQEXSEADSoundObjectObstructionState : uint8 {
    None,
    Detour,
    Obstruction,
    Skip,
};

