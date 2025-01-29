#include "EndChocoboPartsSkeletalMeshComponent.h"

UEndChocoboPartsSkeletalMeshComponent::UEndChocoboPartsSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ColorSettings.AddDefaulted(2);
}

void UEndChocoboPartsSkeletalMeshComponent::SetColorSetting(int32 Layer, const FColor& Color) {
}


