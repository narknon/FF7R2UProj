#pragma once
#include "CoreMinimal.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "EndCinemaEmissiveAnimParams.h"
#include "EndCinemaEmissiveAnimSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCinemaEmissiveAnimSectionTemplate : public FMovieSceneEvalTemplate {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCinemaEmissiveAnimParams Params;
    
public:
    FEndCinemaEmissiveAnimSectionTemplate();
};

