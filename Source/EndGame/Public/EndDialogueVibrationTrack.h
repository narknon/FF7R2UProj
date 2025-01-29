#pragma once
#include "CoreMinimal.h"
#include "MovieSceneNameableTrack.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "EndDialogueVibrationTrack.generated.h"

class UMovieSceneSection;

UCLASS(Blueprintable, MinimalAPI)
class UEndDialogueVibrationTrack : public UMovieSceneNameableTrack/*, public IMovieSceneTrackTemplateProducer*/ {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    TArray<UMovieSceneSection*> Sections;
    
public:
    UEndDialogueVibrationTrack();


    // Fix for true pure virtual functions not being implemented
};

