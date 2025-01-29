#pragma once
#include "CoreMinimal.h"
#include "EndMobRouteSplineCurveDefaults.generated.h"

USTRUCT(BlueprintType)
struct FEndMobRouteSplineCurveDefaults {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DefaultWidth;
    
    ENDGAME_API FEndMobRouteSplineCurveDefaults();
};

