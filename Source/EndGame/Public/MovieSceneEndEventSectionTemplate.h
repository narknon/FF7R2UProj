#pragma once
#include "CoreMinimal.h"
#include "MovieSceneEndEventSectionData.h"
#include "MovieSceneEndEventTemplateBase.h"
#include "MovieSceneEndEventSectionTemplate.generated.h"

USTRUCT(BlueprintType)
struct FMovieSceneEndEventSectionTemplate : public FMovieSceneEndEventTemplateBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndEventSectionData EventData;
    
    ENDGAME_API FMovieSceneEndEventSectionTemplate();
};

