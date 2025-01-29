#include "EndFieldActionVehicleSplineMoveActorBase.h"
#include "EndFieldActionSplineComponent.h"

AEndFieldActionVehicleSplineMoveActorBase::AEndFieldActionVehicleSplineMoveActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->SplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("SplineComponent"));
    this->SplineComponent->SetupAttachment(RootComponent);
}


