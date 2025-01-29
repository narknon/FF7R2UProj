#include "EndShootingGameTargetXYCVSplineActor.h"
#include "EndShootingGameSplineComponent.h"

AEndShootingGameTargetXYCVSplineActor::AEndShootingGameTargetXYCVSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<UEndShootingGameSplineComponent>(TEXT("SplineComponent"));
    this->SplineComponent->SetupAttachment(RootComponent);
}


