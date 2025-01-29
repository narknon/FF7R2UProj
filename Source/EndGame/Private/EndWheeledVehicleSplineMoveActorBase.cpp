#include "EndWheeledVehicleSplineMoveActorBase.h"
#include "Components/SceneComponent.h"
#include "EndWheeledVehicleSplineComponent.h"

AEndWheeledVehicleSplineMoveActorBase::AEndWheeledVehicleSplineMoveActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    this->SplineComponent = CreateDefaultSubobject<UEndWheeledVehicleSplineComponent>(TEXT("SplineComponent"));
    this->MaxSpeed = 60.00f;
    this->SteeringLaneDefault = 0.00f;
    this->SteeringLaneMax = 500.00f;
    this->SteeringLaneKeepTime = 2.00f;
    this->SplineComponent->SetupAttachment(RootComponent);
}


