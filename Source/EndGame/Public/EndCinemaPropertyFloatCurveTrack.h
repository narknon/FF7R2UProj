#pragma once
#include "CoreMinimal.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "Tracks/MovieScenePropertyTrack.h"
#include "EndCinemaPropertyFloatCurveTrack.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaPropertyFloatCurveTrack : public UMovieScenePropertyTrack/*, public IMovieSceneTrackTemplateProducer*/ {
    GENERATED_BODY()
public:
    UEndCinemaPropertyFloatCurveTrack();


    // Fix for true pure virtual functions not being implemented
};

