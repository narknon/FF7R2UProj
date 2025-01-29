#include "EndBikeZeroOneSeComponent.h"

UEndBikeZeroOneSeComponent::UEndBikeZeroOneSeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->VelocityZeroOneFadeTime = 0.50f;
    this->BodyRoughnessThreshold = 0.50f;
    this->RandomPitchRange = 0.20f;
}


