#pragma once
#include "CoreMinimal.h"
#include "EEndStreamLevelCollisionType.generated.h"

UENUM()
enum class EEndStreamLevelCollisionType : int32 {
    Invalid,
    Capsule,
    Box,
};

