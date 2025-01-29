#pragma once
#include "CoreMinimal.h"
#include "EEndAISensorDangerObjectDodgeDirectionType.generated.h"

UENUM(BlueprintType)
enum class EEndAISensorDangerObjectDodgeDirectionType : uint8 {
    Auto,
    Left,
    Right,
    Back,
    Side,
    Front,
    DmgLeft,
    DmgRight,
    DmgSide,
    DmgBack,
    DmgFront,
    RelLeft,
    RelRight,
    RelSide,
    RelBack,
    RelFront,
};

