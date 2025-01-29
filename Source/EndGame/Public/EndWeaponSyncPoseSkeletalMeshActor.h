#pragma once
#include "CoreMinimal.h"
#include "EndWeaponSkeletalMeshActor.h"
#include "EndWeaponSyncPoseSkeletalMeshActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndWeaponSyncPoseSkeletalMeshActor : public AEndWeaponSkeletalMeshActor {
    GENERATED_BODY()
public:
    AEndWeaponSyncPoseSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

};

