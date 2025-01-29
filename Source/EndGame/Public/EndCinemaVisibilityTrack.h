#pragma once
#include "CoreMinimal.h"
#include "Tracks/MovieSceneBoolTrack.h"
#include "EndCinemaVisibilityTrack.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaVisibilityTrack : public UMovieSceneBoolTrack {
    GENERATED_BODY()
public:
    UEndCinemaVisibilityTrack();

};

