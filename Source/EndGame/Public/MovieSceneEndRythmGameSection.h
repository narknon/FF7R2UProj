#pragma once
#include "CoreMinimal.h"
#include "Curves/NameCurve.h"
#include "MovieSceneSection.h"
#include "MovieSceneEndEventSectionData.h"
#include "MovieSceneEndRythmGameSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEndRythmGameSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNameCurve Events;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndEventSectionData EventData;
    
public:
    UMovieSceneEndRythmGameSection();

};

