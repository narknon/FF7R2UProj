#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndShootingGameTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndShootingGameTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndShootingGameTemplate();
};

