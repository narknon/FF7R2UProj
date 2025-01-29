#include "EndMobCrowdGroup.h"

FEndMobCrowdGroup::FEndMobCrowdGroup() {
    this->SkeletalMesh = NULL;
    this->AnimSequence = NULL;
    this->AnimStartTimeRate = 0.00f;
    this->AttachMesh = NULL;
    this->StaticMesh = NULL;
    this->AttachStaticMesh = NULL;
    this->MasterComponent = NULL;
    this->MasterAttachComponent = NULL;
    this->InstancedStaticMeshComponent = NULL;
    this->InstancedAttachStaticMeshComponent = NULL;
}

