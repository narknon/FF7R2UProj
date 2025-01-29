#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EndEnvQueryConditional_IsUCPCVehicleWeapon.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryConditional_IsUCPCVehicleWeapon : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bExcludeAutoPlay;
    
    UEndEnvQueryConditional_IsUCPCVehicleWeapon();

};

