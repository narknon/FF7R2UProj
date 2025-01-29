#pragma once
#include "CoreMinimal.h"
#include "EEndActorTickDependencyLayer.generated.h"

UENUM(BlueprintType)
enum class EEndActorTickDependencyLayer : uint8 {
    Cinema,
    MiniGame,
    FieldAction,
    Battle,
    MobPrefab,
    SyncPoseComponent,
    SyncAnimation,
    SyncAction,
    MovementBase,
    MovementSubBase,
    AnimationControlActor,
    ChocoboParts,
    BoneAttach,
    AttachRootCapsule,
    AttachMeshComponent,
    Setup,
};

