#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndPlayerVehicleType.h"
#include "EndVehicleDisableInOutSplineActor.generated.h"

class UEndVehicleDisableInOutSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndVehicleDisableInOutSplineActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndPlayerVehicleType TatgetVehicleType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndVehicleDisableInOutSplineComponent* SplineComponent;
    
public:
    AEndVehicleDisableInOutSplineActor(const FObjectInitializer& ObjectInitializer);

};

