#pragma once
#include "CoreMinimal.h"
#include "ECastShadowDisableMask.generated.h"

UENUM(BlueprintType)
enum class ECastShadowDisableMask : uint8 {
    ECastShadowDisableMask_ANIMATION,
    ECastShadowDisableMask_MOB_PREFAB,
    ECastShadowDisableMask_VOLUME,
    ECastShadowDisableMask_CINEMA,
    ECastShadowDisableMask_MINIGAME,
    ECastShadowDisableMask_DEBUG,
};

