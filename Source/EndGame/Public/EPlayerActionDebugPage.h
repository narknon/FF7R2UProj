#pragma once
#include "CoreMinimal.h"
#include "EPlayerActionDebugPage.generated.h"

UENUM(BlueprintType)
namespace EPlayerActionDebugPage {
    enum Type {
        None,
        DebugMove,
        JumpArrivalPoint,
        ClimbingPoint,
        NaviEdgeStep,
        Door,
        Movement,
        Trace,
        State,
        FieldActors,
        ShootingTarget,
        TriggerEffect,
        DeadZoneCamera,
        NaviLink,
        ComponentField,
        Max,
    };
}

