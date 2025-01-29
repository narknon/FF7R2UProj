#pragma once
#include "CoreMinimal.h"
#include "ETextureForceResidentMask.generated.h"

UENUM(BlueprintType)
enum class ETextureForceResidentMask : uint8 {
    ETextureForceResidentMask_PLAN_EVENT,
    ETextureForceResidentMaskk_CINEMA,
    ETextureForceResidentMask_SKILL_CAMERA,
    ETextureForceResidentMask_ANIMATION,
    ETextureForceResidentMask_MINIGAME,
    ETextureForceResidentMask_BATTLE,
    ETextureForceResidentMask_VEHICLE,
    ETextureForceResidentMask_MENU,
    ETextureForceResidentMask_DEBUG,
};

