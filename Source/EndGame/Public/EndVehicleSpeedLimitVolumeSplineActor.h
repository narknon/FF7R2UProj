#pragma once
#include "CoreMinimal.h"
#include "EndVehicleRestrictedAreaSplineCollisionActor.h"
#include "EndVehicleSpeedLimitVolumeInterface.h"
#include "EndVehicleSpeedLimitVolumeSplineActor.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndVehicleSpeedLimitVolumeSplineActor : public AEndVehicleRestrictedAreaSplineCollisionActor, public IEndVehicleSpeedLimitVolumeInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetSpeedTowardSplineNormal;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DisableStoryFlag;
    
public:
    AEndVehicleSpeedLimitVolumeSplineActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

