#pragma once
#include "CoreMinimal.h"
#include "ESimpleInteractTargetEditMask.generated.h"

UENUM(BlueprintType)
enum class ESimpleInteractTargetEditMask : uint8 {
    ESITargetEditMask_None,
    ESITargetEditMask_LocationX,
    ESITargetEditMask_LocationY,
    ESITargetEditMask_LocationZ = 4,
    ESITargetEditMask_Yaw = 8,
    ESITargetEditMask_Roll = 16,
    ESITargetEditMask_Pitch = 32,
    ESITargetEditMask_Location_ALL = 7,
    ESITargetEditMask_Rotation_ALL = 56,
    ESITargetEditMask_ALL = 63,
};

