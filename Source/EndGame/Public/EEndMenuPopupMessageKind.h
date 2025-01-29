#pragma once
#include "CoreMinimal.h"
#include "EEndMenuPopupMessageKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuPopupMessageKind : uint8 {
    None,
    Damage,
    Heal,
    PartyDamage,
    MpDamage,
    MpHeal,
    Dodge,
    EnemyDodge,
    StealFailed,
    AlreadyStolen,
    NothingToSteal,
    LevelUp,
    CatchStart,
    CatchEnd,
    MountStart,
    MountEnd,
    JumpStart,
    JumpEnd,
    StealSucceeded,
    LevelUpMateria,
    UpgradeWeapon,
    Death,
    Learning,
    Area,
    Reject,
    NoEffect,
    LevelUpWeapon,
    TargetDestroyed,
    Recover,
    Danger,
    YuffieDodge,
    MorphFailed,
    DownLight,
    DownNormal,
    DownHeavy,
    DownHeavyAir,
};

