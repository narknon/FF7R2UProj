#pragma once
#include "CoreMinimal.h"
#include "EActorMoveMode.generated.h"

UENUM(BlueprintType)
enum class EActorMoveMode : uint8 {
    Ground,
    Fly,
    Other,
    None,
};

