#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADAutoSeMotionSoundType.generated.h"

UENUM(BlueprintType)
namespace ESQEXSEADAutoSeMotionSoundType {
    enum Type {
        None,
        Walk,
        Run,
        Jump,
        LandNormal,
        LandHard,
        FootShuffle,
        Stairs,
        WallTouch,
        RustleArm,
        RustleFoot,
        RustleFootCrotch,
        RustleFootBend,
        WingFlapUp,
        WingFlapDown,
        SwingKnock,
        SwingRub,
        Turn,
        RustleHandWave,
        HeadRot,
        Bow,
        RagdollBounce,
        RagdollFricative,
    };
}

