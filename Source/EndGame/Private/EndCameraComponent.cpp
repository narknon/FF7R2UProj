#include "EndCameraComponent.h"

UEndCameraComponent::UEndCameraComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->FocalLength = 0.00f;
    this->FocusDistance = 0.00f;
    this->FilmWidth = 0.00f;
    this->Roll = 0.00f;
}

void UEndCameraComponent::SetRoll(float NewValue) {
}

void UEndCameraComponent::SetHorizontalAperture(float NewValue) {
}

void UEndCameraComponent::SetFocusDistance(float NewValue) {
}

void UEndCameraComponent::SetFocalLength(float NewValue) {
}


