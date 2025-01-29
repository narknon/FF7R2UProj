#pragma once
#include "CoreMinimal.h"
#include "FEndFieldActionTracePreset.generated.h"

UENUM(BlueprintType)
namespace FEndFieldActionTracePreset {
    enum Type {
        None,
        Move,
        Icon,
        Background,
        Visual,
        Camera,
        Projectile,
        Trigger,
        Water,
        IK,
        NaviEdge,
        Physics,
        NavBuild,
        SyncMove,
        SyncIcon,
        SyncBackground,
        SyncVisual,
        SyncCamera,
        SyncProjectile,
        SyncTrigger,
        SyncWater,
        SyncIK,
        SyncNaviEdge,
        SyncPhysics,
        SyncNavBuild,
        Max,
        SyncStart = SyncMove,
    };
}

