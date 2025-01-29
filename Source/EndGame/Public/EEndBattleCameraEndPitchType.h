#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraEndPitchType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraEndPitchType : uint8 {
    ResetValue,
    SkillCameraRot,
    PlayerLeaderToSkillCameraAim,
    PlayerLeaderToSkillCameraOwner,
    None,
};

