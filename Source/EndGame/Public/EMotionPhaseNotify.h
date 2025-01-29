#pragma once
#include "CoreMinimal.h"
#include "EMotionPhaseNotify.generated.h"

UENUM(BlueprintType)
enum class EMotionPhaseNotify : uint8 {
    MP_InjectionCancel,
    MP_InjectionEffect,
    MP_SelectRotation,
    Num,
};

