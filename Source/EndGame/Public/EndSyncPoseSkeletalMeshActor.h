#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActor.h"
#include "EndSyncPoseSkeletalMeshActor.generated.h"

UCLASS(Blueprintable)
class AEndSyncPoseSkeletalMeshActor : public AEndSkeletalMeshActor {
    GENERATED_BODY()
public:
    AEndSyncPoseSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

};

