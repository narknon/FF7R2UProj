#pragma once
#include "CoreMinimal.h"
#include "ERigUnit_EndPBD_Constraint.generated.h"

UENUM(BlueprintType)
enum class ERigUnit_EndPBD_Constraint : uint8 {
    None,
    Distance,
    Bend,
    CharacterWeight,
    Anim,
    LastPosition,
};

