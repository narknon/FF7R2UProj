#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsUCPCVehicleWeapon.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsUCPCVehicleWeapon : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bPureUCPCOnly;
    
    UEndBTDecorator_IsUCPCVehicleWeapon();

};

