#include "EndCrowdActorBase.h"
#include "Components/SceneComponent.h"

AEndCrowdActorBase::AEndCrowdActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    this->FadeInWaitTime = 0.00f;
    this->OverrideFadeInTime = -1.00f;
    this->OverrideFadeOutTime = -1.00f;
    this->EffectTemplate = NULL;
}

void AEndCrowdActorBase::Stop(float BlendTime, bool bUseFade) {
}

void AEndCrowdActorBase::Play(float BlendTime, bool bUseFade) {
}


