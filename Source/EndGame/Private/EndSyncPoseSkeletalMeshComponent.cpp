#include "EndSyncPoseSkeletalMeshComponent.h"

UEndSyncPoseSkeletalMeshComponent::UEndSyncPoseSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SyncPoseTarget = NULL;
    this->bAttachParentIsMasterPose = false;
}


