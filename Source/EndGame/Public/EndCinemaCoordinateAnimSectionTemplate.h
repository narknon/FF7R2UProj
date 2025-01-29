#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndCinemaCoordinateAnimParams.h"
#include "EndCinemaCoordinateAnimSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCinemaCoordinateAnimSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCinemaCoordinateAnimParams Params;
    
public:
    FEndCinemaCoordinateAnimSectionTemplate();
};

