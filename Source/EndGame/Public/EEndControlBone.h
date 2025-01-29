#pragma once
#include "CoreMinimal.h"
#include "EEndControlBone.generated.h"

UENUM(BlueprintType)
enum class EEndControlBone : uint8 {
    Hip,
    HandL,
    HandR,
    FootL,
    FootR,
    Head,
};

