#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Channels/MovieSceneChannel.h"
#include "EndEventPayload.h"
#include "MovieSceneEndEventSectionData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FMovieSceneEndEventSectionData : public FMovieSceneChannel {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FFrameNumber> Times;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndEventPayload> KeyValues;
    
public:
    FMovieSceneEndEventSectionData();
};

