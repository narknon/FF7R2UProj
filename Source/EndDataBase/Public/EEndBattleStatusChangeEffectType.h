#pragma once
#include "CoreMinimal.h"
#include "EEndBattleStatusChangeEffectType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleStatusChangeEffectType : uint8 {
    None,
    Regene,
    TakePhysicsDamageCoeficient,
    TakeMagicDamageCoeficient,
    Reflect,
    Shield,
    ATBCoefficient,
    Resist,
    Reraise,
    PhysicsAttackCoefficient,
    PhysicsDefenseCoefficient,
    MagicAttackCoefficient,
    MagicDefenseCoefficient,
    Poison,
    TakeDamage_LimitGaugeCoefficient,
    Silence,
    Sleep,
    Stop,
    Berserk,
    Frog,
    Stun,
    GradualPetrify,
    Petrify,
    Particle,
    LastLeave,
    DeathSentence,
    Darkness,
    CriticalRateAdd,
};

