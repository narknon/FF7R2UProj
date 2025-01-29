#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndDialogueVoiceSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndDialogueVoiceSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndDialogueVoiceSectionTemplate();
};

