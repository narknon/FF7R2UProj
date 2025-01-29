#pragma once
#include "CoreMinimal.h"
#include "Curves/NameCurve.h"
#include "MovieSceneSection.h"
#include "MovieSceneEndEventSectionData.h"
#include "MovieSceneEndLovelessPlaySection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEndLovelessPlaySection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNameCurve Events;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndEventSectionData EventData;
    
public:
    UMovieSceneEndLovelessPlaySection();

};

