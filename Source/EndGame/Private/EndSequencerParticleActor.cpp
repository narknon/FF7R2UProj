#include "EndSequencerParticleActor.h"
#include "Components/SceneComponent.h"

AEndSequencerParticleActor::AEndSequencerParticleActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


