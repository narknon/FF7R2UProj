#pragma once
#include "CoreMinimal.h"
#include "EndWheeledVehicleCameraFocusVehicleData.h"
#include "EndWheeledVehicleCameraLocationData.h"
#include "EndWheeledVehicleActionAppearCameraParam.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleActionAppearCameraParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleCameraLocationData FocusPlayerHand;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleCameraFocusVehicleData FocusVehicle;
    
    ENDGAME_API FEndWheeledVehicleActionAppearCameraParam();
};

