#include "EndCinemaMovieSequenceActor.h"
#include "MediaSoundComponent.h"

AEndCinemaMovieSequenceActor::AEndCinemaMovieSequenceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UMediaSoundComponent>(TEXT("MediaSoundComponent"))) {
    this->MediaSoundComponent = (UMediaSoundComponent*)RootComponent;
}


