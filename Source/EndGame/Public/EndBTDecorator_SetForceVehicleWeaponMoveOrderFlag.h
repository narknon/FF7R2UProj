#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_SetForceVehicleWeaponMoveOrderFlag.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_SetForceVehicleWeaponMoveOrderFlag : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Value;
    
    UEndBTDecorator_SetForceVehicleWeaponMoveOrderFlag();

};

