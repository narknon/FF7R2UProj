#pragma once
#include "CoreMinimal.h"
#include "EndVehicleAutoStartOnMoveSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleAutoStartOnMoveSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoStartOnMoveVelocityThreshold;
    
    ENDGAME_API FEndVehicleAutoStartOnMoveSetting();
};

