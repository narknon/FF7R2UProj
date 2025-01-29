#pragma once
#include "CoreMinimal.h"
#include "EEndFootIKModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndFootIKModifierType : uint8 {
    None,
    ForceDisableFootIK,
    EnableCutSceneFootIK,
    DisableGroundFit,
    FullFootLandingRate,
    Max,
};

