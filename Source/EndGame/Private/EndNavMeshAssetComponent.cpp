#include "EndNavMeshAssetComponent.h"

UEndNavMeshAssetComponent::UEndNavMeshAssetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Mobility = EComponentMobility::Static;
}


