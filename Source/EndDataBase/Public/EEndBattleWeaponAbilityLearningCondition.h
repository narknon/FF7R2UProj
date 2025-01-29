#pragma once
#include "CoreMinimal.h"
#include "EEndBattleWeaponAbilityLearningCondition.generated.h"

UENUM(BlueprintType)
enum class EEndBattleWeaponAbilityLearningCondition : uint8 {
    None,
    Activity,
    Hit,
    HitMulti,
    HitBurst,
    Burst,
    Kill,
    HitCancelNormalAttack,
    EnergyChargeMax,
    AerithAssistCreateDamage,
    HitAttributeWeakInYuffieAttributeBuffAbility,
    InvincibleDodge,
    HitFirstUsedATBGaugeMAX,
    UseSpecialBullet,
    HitAttributeWeak,
    KillUpgradeOffensiveModeAttack,
    ATBCharge,
    BurstUpgradeSelfBuffNormalAttack,
    KillCastMagicFieldChangeAbility,
    PartyMemberDangerOrDead,
    HitPartyMember3,
    UseRevengeGaugeMax,
    KillCloneTechnique,
    DiceNumber,
    KillMoogleSummon,
    HitOnDeadCreateDamageSource,
    Danger,
};

