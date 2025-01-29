#include "EndCinemaSequenceActor.h"
#include "Components/SceneComponent.h"
#include "EndCinemaSequencePlayer.h"

AEndCinemaSequenceActor::AEndCinemaSequenceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndCinemaSequencePlayer>(TEXT("AnimationPlayer"))) {
    this->SequenceWrapper = NULL;
    this->LayoutOffsetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("LayoutOffsetComponent"));
    this->LayoutOffsetComponent->SetupAttachment(RootComponent);
}


