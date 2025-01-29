#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndDialogueCommandSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndDialogueCommandSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndDialogueCommandSectionTemplate();
};

