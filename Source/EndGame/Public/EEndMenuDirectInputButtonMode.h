#pragma once
#include "CoreMinimal.h"
#include "EEndMenuDirectInputButtonMode.generated.h"

UENUM(BlueprintType)
enum class EEndMenuDirectInputButtonMode : uint8 {
    Numerical,
    Alphabetical,
    Symbolic,
};

