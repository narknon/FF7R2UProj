#pragma once
#include "CoreMinimal.h"
#include "Curves/NameCurve.h"
#include "MovieSceneSection.h"
#include "MovieSceneEndShootingGameSectionData.h"
#include "MovieSceneEndShootingGameSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEndShootingGameSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNameCurve Events;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndShootingGameSectionData EventData;
    
public:
    UMovieSceneEndShootingGameSection();

};

