#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraTargetType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraTargetType : uint8 {
    None,
    OwnerMesh,
    TargetMesh,
    PlayerLeaderMesh,
    OwnerActor,
    TargetActor,
    PlayerLeaderActor,
    DamageSourceGenerated,
    DamageSourceHit,
    AimPoint,
    WorldOrigin,
    OwnerLatestPositionHit,
    TargetLatestPositionHit,
    PlayerLeaderLatestPositionHit,
    FieldCamera,
    SummonMesh,
    SummonActor,
    ActorNameMesh,
    ActorNameActor,
    CharaIDMesh,
    CharaIDActor,
    TargetPoint,
    DamageSourceID,
    TargetLockPos,
    OwnerFloor,
    TargetFloor,
    MenuPartyMemberMesh,
};

