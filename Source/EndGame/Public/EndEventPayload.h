#pragma once
#include "CoreMinimal.h"
#include "MovieSceneEndEventParameters.h"
#include "EndEventPayload.generated.h"

USTRUCT(BlueprintType)
struct FEndEventPayload {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEndEventParameters Parameters;
    
    ENDGAME_API FEndEventPayload();
};

