#pragma once
#include "CoreMinimal.h"
#include "EBikeDamageMotionType.generated.h"

UENUM(BlueprintType)
enum class EBikeDamageMotionType : uint8 {
    Normal,
    Explosion,
    KnockBack_LR1,
    KnockBack_F,
    KnockBack_LR2,
};

