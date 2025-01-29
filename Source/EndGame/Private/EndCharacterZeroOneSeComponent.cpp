#include "EndCharacterZeroOneSeComponent.h"

UEndCharacterZeroOneSeComponent::UEndCharacterZeroOneSeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PropertyValueMax = 100.00f;
    this->FadeInTime = 0.00f;
    this->FadeOutTime = 0.00f;
    this->bAttatch = true;
    this->bDefaultEnable = false;
    this->bEnableSlot0 = true;
    this->Slot0Property = EEndCharacterZeroOneSeProperties::Velocity;
    this->bEnableSlot1 = true;
    this->Slot1Property = EEndCharacterZeroOneSeProperties::Velocity;
}


