#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndRythmGameTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndRythmGameTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndRythmGameTemplate();
};

