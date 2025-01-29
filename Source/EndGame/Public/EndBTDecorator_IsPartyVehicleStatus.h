#pragma once
#include "CoreMinimal.h"
#include "EEndPlayerVehicleType.h"
#include "EPartyVehicleRideStatus.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsPartyVehicleStatus.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsPartyVehicleStatus : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndPlayerVehicleType VehicleTypey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EPartyVehicleRideStatus> VehicleRideStatus;
    
    UEndBTDecorator_IsPartyVehicleStatus();

};

