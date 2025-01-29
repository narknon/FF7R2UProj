#pragma once
#include "CoreMinimal.h"
#include "Channels/MovieSceneBoolChannel.h"
#include "Evaluation/MovieScenePropertyTemplate.h"
#include "EndCinemaVisibilitySectionTemplateBase.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaVisibilitySectionTemplateBase : public FMovieScenePropertySectionTemplate {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneBoolChannel BoolCurve;
    
public:
    ENDGAME_API FEndCinemaVisibilitySectionTemplateBase();
};

