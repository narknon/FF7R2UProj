#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndToroccoTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndToroccoTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndToroccoTemplate();
};

