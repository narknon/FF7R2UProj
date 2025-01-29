#pragma once
#include "CoreMinimal.h"
#include "EEndStateAttribute.generated.h"

UENUM(BlueprintType)
enum class EEndStateAttribute : uint8 {
    OnOff,
    BeginOverlapTrigger,
    Effect,
    PlannerLevelSet,
    AI,
    TargetIcon,
    General,
    Attribute07,
    EnvironmentAnimation,
    EndOverlapTrigger,
    ResponseAreaAction,
    MotionState,
    EnvironmentAnimationInnerOuter,
    AttachActor0,
    AttachActor1,
    AttachActor2,
    SideDestination,
    DisableLookAt,
    AttachActor3,
    InterestPoint,
    Attribute20,
    Attribute21,
    Attribute22,
    Attribute23,
    Attribute24,
    Attribute25,
    Attribute26,
    Attribute27,
    DebugDebugDebug,
    BattleScene,
    PlacementEnvironmentSet,
    PlacementPlannerLevelSet,
    AttributeMax,
    None,
};

