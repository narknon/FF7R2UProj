#pragma once
#include "CoreMinimal.h"
#include "EFieldAiPathWayType.generated.h"

UENUM(BlueprintType)
enum class EFieldAiPathWayType : uint8 {
    None,
    Center,
    Right,
    Left,
    Max,
};

