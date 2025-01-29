#pragma once
#include "CoreMinimal.h"
#include "EEndLookAroundState.generated.h"

UENUM(BlueprintType)
enum class EEndLookAroundState : uint8 {
    None,
    Wait,
    Left,
    Right,
};

