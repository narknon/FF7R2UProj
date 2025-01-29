#pragma once
#include "CoreMinimal.h"
#include "MovieSceneNameableTrack.h"
#include "EndCinemaSceneLightCurveTrack.generated.h"

class UMovieSceneSection;

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaSceneLightCurveTrack : public UMovieSceneNameableTrack {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UMovieSceneSection*> Sections;
    
public:
    UEndCinemaSceneLightCurveTrack();

};

