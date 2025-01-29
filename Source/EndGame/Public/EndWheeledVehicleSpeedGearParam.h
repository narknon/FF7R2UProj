#pragma once
#include "CoreMinimal.h"
#include "EndWheeledVehicleSpeedGearParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleSpeedGearParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpeedKph;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GearNum;
    
    ENDGAME_API FEndWheeledVehicleSpeedGearParam();
};

