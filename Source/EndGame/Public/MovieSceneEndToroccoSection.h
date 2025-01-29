#pragma once
#include "CoreMinimal.h"
#include "Curves/NameCurve.h"
#include "MovieSceneSection.h"
#include "MovieSceneEndToroccoSectionData.h"
#include "MovieSceneEndToroccoSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEndToroccoSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNameCurve Events;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndToroccoSectionData EventData;
    
public:
    UMovieSceneEndToroccoSection();

};

