#pragma once
#include "CoreMinimal.h"
#include "EndWheeledVehicleSplineMoveActorBase.h"
#include "EndWheeledVehicleSplineMoveActor.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndWheeledVehicleSplineMoveActor : public AEndWheeledVehicleSplineMoveActorBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CameraModuleName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSetTransformOnStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSetSpeedOnStart;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SpeedOnStartKph;
    
public:
    AEndWheeledVehicleSplineMoveActor(const FObjectInitializer& ObjectInitializer);

};

