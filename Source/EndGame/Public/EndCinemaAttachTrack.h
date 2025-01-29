#pragma once
#include "CoreMinimal.h"
#include "MovieSceneTrack.h"
#include "EndCinemaAttachTrack.generated.h"

class UMovieSceneSection;

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaAttachTrack : public UMovieSceneTrack {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UMovieSceneSection*> ConstraintSections;
    
public:
    UEndCinemaAttachTrack();

};

