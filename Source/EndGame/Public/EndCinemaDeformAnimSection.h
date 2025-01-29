#pragma once
#include "CoreMinimal.h"
#include "Channels/MovieSceneFloatChannel.h"
#include "MovieSceneSection.h"
#include "EndCinemaDeformAnimParams.h"
#include "EndCinemaDeformAnimSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaDeformAnimSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCinemaDeformAnimParams Params;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneFloatChannel FloatCurve;
    
    UEndCinemaDeformAnimSection();

};

