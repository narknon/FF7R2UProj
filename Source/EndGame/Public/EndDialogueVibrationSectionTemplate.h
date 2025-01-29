#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndDialogueVibrationSectionTemplate.generated.h"

class UEndDialogueVibrationPreset;

USTRUCT(BlueprintType)
struct FEndDialogueVibrationSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndDialogueVibrationPreset* Preset;
    
public:
    ENDGAME_API FEndDialogueVibrationSectionTemplate();
};

