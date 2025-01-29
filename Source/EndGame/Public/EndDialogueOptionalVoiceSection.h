#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "EndDialogueOptionalVoiceSection.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndDialogueOptionalVoiceSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName OwnerBindName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName VoiceLabel;
    
public:
    UEndDialogueOptionalVoiceSection();

};

