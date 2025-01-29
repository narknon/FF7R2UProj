#pragma once
#include "CoreMinimal.h"
#include "EAttachBarretSunglassAnimation.generated.h"

UENUM(BlueprintType)
enum class EAttachBarretSunglassAnimation : uint8 {
    WearingSunglasses,
    FinishWearingSunglasses,
    InProcess_Wearing,
    StartWearingSunglasses,
    RemovedSunglasses,
    FinishRemovingSunglasses,
    InProcess_Removing,
    StartRemovingSunglasses,
    Battle_GlassesVisible,
    Battle_GlassesInvisible,
};

