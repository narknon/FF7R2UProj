#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndDialogueOptionalVoiceSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct FEndDialogueOptionalVoiceSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
    ENDGAME_API FEndDialogueOptionalVoiceSectionTemplate();
};

