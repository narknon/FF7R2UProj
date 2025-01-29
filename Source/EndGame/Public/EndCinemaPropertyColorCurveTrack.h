#pragma once
#include "CoreMinimal.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "Tracks/MovieScenePropertyTrack.h"
#include "EndCinemaPropertyColorCurveTrack.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaPropertyColorCurveTrack : public UMovieScenePropertyTrack/*, public IMovieSceneTrackTemplateProducer*/ {
    GENERATED_BODY()
public:
    UEndCinemaPropertyColorCurveTrack();


    // Fix for true pure virtual functions not being implemented
};

