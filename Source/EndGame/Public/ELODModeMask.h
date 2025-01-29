#pragma once
#include "CoreMinimal.h"
#include "ELODModeMask.generated.h"

UENUM(BlueprintType)
enum class ELODModeMask : uint8 {
    ELODModeMask_PLAN_EVENT,
    ELODModeMask_CINEMA,
    ELODModeMask_SKILL_CAMERA,
    ELODModeMask_ANIMATION,
    ELODModeMask_MINIGAME,
    ELODModeMask_BATTLE,
    ELODModeMask_VEHICLE,
    ELODModeMask_NOTIFY,
    ELODModeMask_MENU,
    ELODModeMask_DEBUG,
    ELODModeLevelMask_Max UMETA(Hidden),
};

