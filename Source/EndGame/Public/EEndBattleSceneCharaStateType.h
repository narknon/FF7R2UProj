#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSceneCharaStateType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSceneCharaStateType : uint8 {
    Dead,
    SyncAction,
    Stun,
    StatusChangePoison,
    StatusChangeHighlyPoison,
    StatusChangeFury,
    StatusChangeSadness,
    StatusChangeSilence,
    StatusChangeSleep,
    StatusChangeSlow,
    StatusChangeStop,
    StatusChangePrePetrify,
    StatusChangePetrify,
    StatusChangeBerserk,
    StatusChangeFrog,
    StatusChangeDeathSentence,
    StatusChangeDeath,
    DamageReactionSmall,
    DamageReactionMediun,
    DamageReactionLarge,
    DamageReactionLaunch,
    DamageReactionBlow,
    DamageReactionStrike,
    DamageReactionMotion,
    DamageReactionRepel,
    Other,
};

