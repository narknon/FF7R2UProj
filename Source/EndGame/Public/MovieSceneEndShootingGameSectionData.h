#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Channels/MovieSceneChannel.h"
#include "EndShootingGamePayload.h"
#include "MovieSceneEndShootingGameSectionData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FMovieSceneEndShootingGameSectionData : public FMovieSceneChannel {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FFrameNumber> Times;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndShootingGamePayload> KeyValues;
    
public:
    FMovieSceneEndShootingGameSectionData();
};

