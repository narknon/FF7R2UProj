#include "EndCylinderComponent.h"

UEndCylinderComponent::UEndCylinderComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bUseEditorCompositing = true;
    this->CylinderHalfHeight = 50.00f;
    this->CylinderRadius = 50.00f;
    this->CylinderSides = 16;
}

void UEndCylinderComponent::SetCylinderSize(float InRadius, float InHalfHeight, int32 InCylinderSides, bool bUpdateOverlaps) {
}

float UEndCylinderComponent::GetUnscaledCylinderRadius() const {
    return 0.0f;
}

float UEndCylinderComponent::GetUnscaledCylinderHalfHeight() const {
    return 0.0f;
}

float UEndCylinderComponent::GetScaledCylinderRadius() const {
    return 0.0f;
}

float UEndCylinderComponent::GetScaledCylinderHalfHeight() const {
    return 0.0f;
}

int32 UEndCylinderComponent::GetCylinderSides() const {
    return 0;
}


