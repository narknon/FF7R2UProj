#include "EndShootingGameTargetSplineActor.h"
#include "EndShootingGameSplineComponent.h"

AEndShootingGameTargetSplineActor::AEndShootingGameTargetSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<UEndShootingGameSplineComponent>(TEXT("SplineComponent"));
    this->SplineComponent->SetupAttachment(RootComponent);
}


