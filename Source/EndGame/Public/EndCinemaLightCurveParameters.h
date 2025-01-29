#pragma once
#include "CoreMinimal.h"
#include "EndCinemaLightCurveParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaLightCurveParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetPropertyName;
    
    ENDGAME_API FEndCinemaLightCurveParameters();
};

