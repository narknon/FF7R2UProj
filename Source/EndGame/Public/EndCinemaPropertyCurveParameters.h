#pragma once
#include "CoreMinimal.h"
#include "EndCinemaPropertyCurveParameters.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaPropertyCurveParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetPropertyName;
    
    ENDGAME_API FEndCinemaPropertyCurveParameters();
};

