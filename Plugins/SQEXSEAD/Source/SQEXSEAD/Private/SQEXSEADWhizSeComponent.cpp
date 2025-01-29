#include "SQEXSEADWhizSeComponent.h"

USQEXSEADWhizSeComponent::USQEXSEADWhizSeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->WhizSoundAsset = NULL;
    this->ApproachJudgmentDistance = 250.00f;
    this->ApproachJudgmentVelocity = 0.00f;
    this->bFollow = true;
    this->bOnlyOnce = true;
    this->bUseRelativeVelocity = false;
    this->MyAudioComponent = NULL;
    this->MyMeshComponent = NULL;
}


