#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Channels/MovieSceneChannel.h"
#include "EndToroccoPayload.h"
#include "MovieSceneEndToroccoSectionData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FMovieSceneEndToroccoSectionData : public FMovieSceneChannel {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FFrameNumber> Times;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndToroccoPayload> KeyValues;
    
public:
    FMovieSceneEndToroccoSectionData();
};

