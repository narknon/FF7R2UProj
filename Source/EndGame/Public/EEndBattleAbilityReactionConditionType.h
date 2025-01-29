#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityReactionConditionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityReactionConditionType : uint8 {
    None,
    Hit,
    Guard,
    TargetDodge,
    TargetDodgeDirection,
    NotTargetFrontAndNear,
    Damage,
    NotifyAIBP,
    NormalAttackDamage,
    AnimationLoopNoInput = 20,
    CombinationPartnerAbilityChargeDamageSourceUnLevelUpDischarge,
    SelfContactWall,
    TargetInsideAngleAndDistance,
    CombinationPartnerAbilitySuspend,
    NextAnimationNoHitDamage,
    CombinationPartnerAbilityGuardReaction,
    CombinationPartnerAbilityGuardEnd,
    Cancel,
};

