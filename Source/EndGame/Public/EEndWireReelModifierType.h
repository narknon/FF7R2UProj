#pragma once
#include "CoreMinimal.h"
#include "EEndWireReelModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndWireReelModifierType : uint8 {
    Attach,
    Launch,
    EnableGravity,
    Keeping,
    Release,
    Detach,
};

