#pragma once
#include "CoreMinimal.h"
#include "EndCinemaCoordinateAnimParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaCoordinateAnimParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    ENDGAME_API FEndCinemaCoordinateAnimParameters();
};

