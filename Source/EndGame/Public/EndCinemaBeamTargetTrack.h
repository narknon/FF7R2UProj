#pragma once
#include "CoreMinimal.h"
#include "MovieSceneTrack.h"
#include "EndCinemaBeamTargetTrack.generated.h"

class UMovieSceneSection;

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaBeamTargetTrack : public UMovieSceneTrack {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UMovieSceneSection*> ConstraintSections;
    
public:
    UEndCinemaBeamTargetTrack();

};

