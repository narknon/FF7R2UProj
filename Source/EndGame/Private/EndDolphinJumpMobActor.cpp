#include "EndDolphinJumpMobActor.h"
#include "Components/SplineComponent.h"

AEndDolphinJumpMobActor::AEndDolphinJumpMobActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    this->StartOffset = 0.00f;
    this->SpeedScale = 1.00f;
}


