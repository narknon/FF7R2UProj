#pragma once
#include "CoreMinimal.h"
#include "EndVehicleSmoothingParam.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleSmoothingParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Acceleration;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ConstantArrivalTime;
    
    ENDGAME_API FEndVehicleSmoothingParam();
};

