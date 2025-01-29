#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndWheeledVehicleRiderReactionParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleRiderReactionParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DeltaSpeedKphForHitWall;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DeltaSpeedKphForBigJump;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinInAirTimeForBigJump;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator VehicleRotationOnPlayGrab;
    
    ENDGAME_API FEndWheeledVehicleRiderReactionParam();
};

