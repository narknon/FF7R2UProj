#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentPhysImpulseParam.h"
#include "EndWheeledVehicleAttackParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleAttackParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EnablePhysicsBreakSpeedKph;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndEnvironmentPhysImpulseParam ImpulseParam;
    
    ENDGAME_API FEndWheeledVehicleAttackParam();
};

