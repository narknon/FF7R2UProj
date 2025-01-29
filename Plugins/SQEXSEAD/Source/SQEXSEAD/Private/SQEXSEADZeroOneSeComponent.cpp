#include "SQEXSEADZeroOneSeComponent.h"

USQEXSEADZeroOneSeComponent::USQEXSEADZeroOneSeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->SoundAsset = NULL;
    this->SoundIndex = 0;
    this->FadeInTime = 0.00f;
    this->FadeOutTime = 0.00f;
    this->AudioStartTiming = ESQEXSEADAudioStartTimings::None;
    this->bEnable_Slot0 = false;
    this->PropertyType_Slot0 = ESQEXSEADZeroOneProperties::None;
    this->bEnable_Slot1 = false;
    this->PropertyType_Slot1 = ESQEXSEADZeroOneProperties::None;
    this->MyAudioComponent = NULL;
}

void USQEXSEADZeroOneSeComponent::Stop() {
}

void USQEXSEADZeroOneSeComponent::SetZeroOneValue(int32 Slot, float Value, float FadeTime) {
}

void USQEXSEADZeroOneSeComponent::Play() {
}


