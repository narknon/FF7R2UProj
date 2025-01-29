#pragma once
#include "CoreMinimal.h"
#include "EChocoboCaptureRodeoPhase.generated.h"

UENUM(BlueprintType)
enum class EChocoboCaptureRodeoPhase : uint8 {
    CCR_AttachStart,
    CCR_DetachStart,
    CCR_FeatherLeftVisible,
    CCR_FeatherLeftHidden,
    CCR_FeatherRightVisible,
    CCR_FeatherRightHidden,
    CCR_StoneHidden,
    CCR_EatingHidden,
    CCR_EnableCancelGetItem,
    CCR_SetReinsConstraint,
    CCR_ResetReinsConstraint,
    Num,
};

