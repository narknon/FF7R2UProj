#pragma once
#include "CoreMinimal.h"
#include "EEndWireReelState.generated.h"

UENUM(BlueprintType)
enum class EEndWireReelState : uint8 {
    Idle,
    Launch,
    Keeping,
    Release,
};

