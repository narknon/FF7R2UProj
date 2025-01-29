#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "Channels/MovieSceneFloatChannel.h"
#include "EndCinemaDeformAnimParams.h"
#include "EndCinemaDeformAnimSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCinemaDeformAnimSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCinemaDeformAnimParams Params;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneFloatChannel FloatChannel;
    
public:
    FEndCinemaDeformAnimSectionTemplate();
};

