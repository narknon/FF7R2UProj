#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndDialogueShotSkipSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndDialogueShotSkipSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndDialogueShotSkipSectionTemplate();
};

