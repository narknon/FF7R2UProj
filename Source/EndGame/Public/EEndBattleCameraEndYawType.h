#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraEndYawType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraEndYawType : uint8 {
    Default,
    SkillCameraRot,
    PlayerLeaderToSkillCameraAim,
    PlayerLeaderToSkillCameraOwner,
    None,
    PlayerLeaderForward,
};

