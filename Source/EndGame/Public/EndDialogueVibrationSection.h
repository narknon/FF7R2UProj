#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "EndDialogueVibrationSection.generated.h"

class UEndDialogueVibrationPreset;

UCLASS(Blueprintable)
class ENDGAME_API UEndDialogueVibrationSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEndDialogueVibrationPreset* Preset;
    
public:
    UEndDialogueVibrationSection();

};

