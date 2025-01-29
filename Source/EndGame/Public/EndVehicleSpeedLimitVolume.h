#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EEndRestrictedAreaVehicleType.h"
#include "EndVehicleSpeedLimitVolumeInterface.h"
#include "EndVehicleSpeedLimitVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndVehicleSpeedLimitVolume : public AVolume, public IEndVehicleSpeedLimitVolumeInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndRestrictedAreaVehicleType TargetVehicleType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DisableStoryFlag;
    
public:
    AEndVehicleSpeedLimitVolume(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

