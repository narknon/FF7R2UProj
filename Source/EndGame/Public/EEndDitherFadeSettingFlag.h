#pragma once
#include "CoreMinimal.h"
#include "EEndDitherFadeSettingFlag.generated.h"

UENUM(BlueprintType)
enum class EEndDitherFadeSettingFlag : uint8 {
    None,
    DisableNearFade,
    EnableNearFadeOnBattle,
    UseEnvironmentMeshSetting = 4,
};

