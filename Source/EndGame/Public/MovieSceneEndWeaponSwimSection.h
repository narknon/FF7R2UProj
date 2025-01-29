#pragma once
#include "CoreMinimal.h"
#include "Curves/NameCurve.h"
#include "MovieSceneSection.h"
#include "MovieSceneEndWeaponSwimSectionData.h"
#include "MovieSceneEndWeaponSwimSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEndWeaponSwimSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FNameCurve Events;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndWeaponSwimSectionData EventData;
    
public:
    UMovieSceneEndWeaponSwimSection();

};

