#pragma once
#include "CoreMinimal.h"
#include "EEndControlBoneCondition.generated.h"

UENUM(BlueprintType)
enum class EEndControlBoneCondition : uint8 {
    None,
    Walk,
    Run,
};

