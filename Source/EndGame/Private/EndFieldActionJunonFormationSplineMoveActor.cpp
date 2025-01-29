#include "EndFieldActionJunonFormationSplineMoveActor.h"
#include "EndFieldActionSplineComponent.h"

AEndFieldActionJunonFormationSplineMoveActor::AEndFieldActionJunonFormationSplineMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<UEndFieldActionSplineComponent>(TEXT("SplineComponent"));
    this->SplineComponent->SetupAttachment(RootComponent);
}


