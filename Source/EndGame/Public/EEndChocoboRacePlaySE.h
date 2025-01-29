#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRacePlaySE.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRacePlaySE : uint8 {
    GetItemAbility,
    GetItemDash,
    GetItemSpeed,
    OpenStartGate,
    BlockMove,
    BombExplosion,
    HitBound,
    BoundJump,
    UseDashOK,
    UseDashNG,
    UseAbilityOK,
    UseAbilityNG,
    BumpHitFenceN,
    BumpHitFenceM,
    BumpHitChocobo,
    BumpHitBoard,
    BumpHitGimmick,
    BumpHitBox,
    BumpHitIronBall,
    BumpHitEtc,
    BumpHitBound,
    Max,
};

