#pragma once
#include "CoreMinimal.h"
#include "EChocoboCameraStateType.generated.h"

UENUM(BlueprintType)
enum class EChocoboCameraStateType : uint8 {
    Normal,
    StartClimb,
    StartClimbDown,
    Climb,
    LeaveClimb,
    Swim,
    LeaveSwim,
    Jet,
    JetCeiling,
    JetGlide,
    JetFall,
    Glide,
    PrepareJump,
    Jump,
    Slide,
    BlendToNormal,
    OverrideCameraMode,
    MAX,
};

