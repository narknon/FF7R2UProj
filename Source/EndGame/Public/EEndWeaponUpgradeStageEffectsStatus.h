#pragma once
#include "CoreMinimal.h"
#include "EEndWeaponUpgradeStageEffectsStatus.generated.h"

UENUM(BlueprintType)
enum class EEndWeaponUpgradeStageEffectsStatus : uint8 {
    None,
    PlayStage,
    WaitCameraMove,
    WaitSpawn,
    WaitActive,
    WaitStage,
    Done,
};

