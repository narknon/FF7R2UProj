#pragma once
#include "CoreMinimal.h"
#include "EEndMobMoveDirectionType.generated.h"

UENUM(BlueprintType)
enum class EEndMobMoveDirectionType : uint8 {
    Plus,
    Minus,
    Invert,
};

