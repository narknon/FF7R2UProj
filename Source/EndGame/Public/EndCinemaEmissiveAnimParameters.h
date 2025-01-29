#pragma once
#include "CoreMinimal.h"
#include "EndCinemaEmissiveAnimParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaEmissiveAnimParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    ENDGAME_API FEndCinemaEmissiveAnimParameters();
};

