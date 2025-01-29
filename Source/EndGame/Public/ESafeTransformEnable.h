#pragma once
#include "CoreMinimal.h"
#include "ESafeTransformEnable.generated.h"

UENUM(BlueprintType)
enum class ESafeTransformEnable : uint8 {
    ESafeTransform_DEBUG,
    ESafeTransform_SYSTEM,
    ESafeTransform_AIMOVE,
    ESafeTransform_ANIMATION,
    ESafeTransform_FIELD,
    ESafeTransform_FIELD_AI,
    ESafeTransform_FIELD_ACTION,
    ESafeTransform_FIELD_CINEMA,
    ESafeTransform_MINIGAME,
    ESafeTransform_BATTLE,
    ESafeTransform_CINEMA,
    ESafeTransform_VEHICLE,
    ESafeTransform_FIELD_COMPONENT,
};

