#pragma once
#include "CoreMinimal.h"
#include "EndWheeledVehicleMovementWaterRestrictionParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleMovementWaterRestrictionParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartLimitWaterDepth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpeedInWater;
    
    ENDGAME_API FEndWheeledVehicleMovementWaterRestrictionParam();
};

