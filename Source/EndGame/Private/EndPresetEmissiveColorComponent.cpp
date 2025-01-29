#include "EndPresetEmissiveColorComponent.h"

UEndPresetEmissiveColorComponent::UEndPresetEmissiveColorComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EmissiveColorPreset = NULL;
    this->Sound = NULL;
    this->Attenuation = NULL;
}


