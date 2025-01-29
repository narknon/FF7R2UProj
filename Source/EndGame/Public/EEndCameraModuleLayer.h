#pragma once
#include "CoreMinimal.h"
#include "EEndCameraModuleLayer.generated.h"

UENUM(BlueprintType)
enum class EEndCameraModuleLayer : uint8 {
    Debug,
    HeightDeadzone,
    IdleHeightStabilizer,
    CharacterAdjust,
    NotifyOverride,
    BattleOffset,
    AdjustLength,
    LockOn,
    StealCamera,
    SweepCenterAdjustments,
    Reset,
    ResetTurnBack,
    SpaceOffset,
    Swim,
    SecondaryCharacter,
    ExtraAction,
    LookAt,
    LookAtTurnBack,
    CustomizableAction,
    AutoRotate,
    Skill,
    Command,
    LeaderChange,
    Scan,
    WaterSurface,
    MAX,
};

