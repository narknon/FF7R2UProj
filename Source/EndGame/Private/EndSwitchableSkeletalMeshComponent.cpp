#include "EndSwitchableSkeletalMeshComponent.h"

UEndSwitchableSkeletalMeshComponent::UEndSwitchableSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAttachParentIsMasterPose = true;
}

void UEndSwitchableSkeletalMeshComponent::SetSkeletalMeshByLabel(FName Label, bool bReinitPose) {
}

void UEndSwitchableSkeletalMeshComponent::SetSkeletalMeshByIndex(int32 Index, bool bReinitPose) {
}


