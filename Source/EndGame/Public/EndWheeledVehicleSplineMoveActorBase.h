#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndVehicleSmoothingParam.h"
#include "EndWheeledVehicleActionActorBase.h"
#include "EndWheeledVehicleSplineMoveMetaData.h"
#include "EndWheeledVehicleSplineMoveActorBase.generated.h"

class UEndWheeledVehicleSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndWheeledVehicleSplineMoveActorBase : public AEndWheeledVehicleActionActorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndWheeledVehicleSplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndWheeledVehicleSplineMoveMetaData> SplineMetadata;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SteeringLaneDefault;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SteeringLaneMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SteeringLaneKeepTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSmoothingParam SteeringLaneInputSmoothing;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSmoothingParam SteeringLaneNoInputSmoothing;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval CheckLocationOffsetPerSpeed;
    
public:
    AEndWheeledVehicleSplineMoveActorBase(const FObjectInitializer& ObjectInitializer);

};

