#include "EndBoneAttachComponent.h"

UEndBoneAttachComponent::UEndBoneAttachComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->OwnerMesh = NULL;
    this->AttachTarget = EEndBoneAttachTarget::None;
    this->AttachTargetMesh = NULL;
}


