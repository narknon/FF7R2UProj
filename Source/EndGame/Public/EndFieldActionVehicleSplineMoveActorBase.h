#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldActionVehicleSplineMoveActorBase.generated.h"

class UEndFieldActionSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionVehicleSplineMoveActorBase : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionSplineComponent* SplineComponent;
    
public:
    AEndFieldActionVehicleSplineMoveActorBase(const FObjectInitializer& ObjectInitializer);

};

