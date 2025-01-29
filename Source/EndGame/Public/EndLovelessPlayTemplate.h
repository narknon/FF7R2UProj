#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndLovelessPlayTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndLovelessPlayTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndLovelessPlayTemplate();
};

