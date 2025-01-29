#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "EndCinemaCoordinateAnimParams.h"
#include "EndCinemaCoordinateAnimSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaCoordinateAnimSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCinemaCoordinateAnimParams Params;
    
    UEndCinemaCoordinateAnimSection();

};

