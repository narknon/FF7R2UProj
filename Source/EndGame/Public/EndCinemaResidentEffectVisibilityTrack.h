#pragma once
#include "CoreMinimal.h"
#include "MovieSceneNameableTrack.h"
#include "EndCinemaResidentEffectVisibilityTrack.generated.h"

class UMovieSceneSection;

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaResidentEffectVisibilityTrack : public UMovieSceneNameableTrack {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UMovieSceneSection*> Sections;
    
public:
    UEndCinemaResidentEffectVisibilityTrack();

};

