#pragma once
#include "CoreMinimal.h"
#include "EEndFieldMovementSettingFlag.generated.h"

UENUM(BlueprintType)
enum class EEndFieldMovementSettingFlag : uint8 {
    EEndFieldMovementSettingFlag_None,
    EEndFieldMovementSettingFlag_DisableOnlyNaviMove,
    EEndFieldMovementSettingFlag_DisableRestrictWaterNavi,
    EEndFieldMovementSettingFlag_UpliftFloorAutoParkour = 4,
    EEndFieldMovementSettingFlag_DisableBumpFromSelfBump = 8,
    EEndFieldMovementSettingFlag_DisableBumpFromOtherBump = 16,
    EEndFieldMovementSettingFlag_FenceBlockToFenceJump = 32,
    EEndFieldMovementSettingFlag_JumpBlockInvalidArea = 64,
};

