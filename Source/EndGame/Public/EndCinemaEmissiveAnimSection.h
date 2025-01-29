#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "EndCinemaEmissiveAnimParams.h"
#include "EndCinemaEmissiveAnimSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UEndCinemaEmissiveAnimSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCinemaEmissiveAnimParams Params;
    
    UEndCinemaEmissiveAnimSection();

};

