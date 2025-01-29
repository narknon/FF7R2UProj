#pragma once
#include "CoreMinimal.h"
#include "EEndControlBoneType.generated.h"

UENUM(BlueprintType)
enum class EEndControlBoneType : uint8 {
    None,
    OffsetComponentSpace,
    OffsetWorldSpace,
    ConstraintComponentSpace,
    ConstraintWorldSpace,
};

