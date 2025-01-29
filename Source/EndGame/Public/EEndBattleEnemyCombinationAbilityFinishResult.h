#pragma once
#include "CoreMinimal.h"
#include "EEndBattleEnemyCombinationAbilityFinishResult.generated.h"

UENUM(BlueprintType)
enum class EEndBattleEnemyCombinationAbilityFinishResult : uint8 {
    TargetDefeated,
    SinglePartyMemberAlive,
    FirstAttackMissed,
    CharacterDamageLimitBroken,
    CharacterDefeated,
    CharacterHitByLimitBreak,
    CharacterBurstActivated,
    CharacterHitByCombinationAttack,
    CharacterHitBySummonAttack,
    AbilityLoopFinished,
};

