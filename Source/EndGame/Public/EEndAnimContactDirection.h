#pragma once
#include "CoreMinimal.h"
#include "EEndAnimContactDirection.generated.h"

UENUM(BlueprintType)
enum class EEndAnimContactDirection : uint8 {
    None,
    ForwardLeft,
    ForwardRight,
    BackLeft,
    BackRight,
};

