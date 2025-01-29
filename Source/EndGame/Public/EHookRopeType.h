#pragma once
#include "CoreMinimal.h"
#include "EHookRopeType.generated.h"

UENUM(BlueprintType)
enum class EHookRopeType : uint8 {
    TarzanRope,
    Climbing,
    MAX,
};

