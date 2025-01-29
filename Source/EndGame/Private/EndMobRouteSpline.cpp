#include "EndMobRouteSpline.h"
#include "EndMobRouteSplineComponent.h"

AEndMobRouteSpline::AEndMobRouteSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndMobRouteSplineComponent>(TEXT("SplineMoveComponent"))) {
    this->IsLoop = true;
    this->SplineMoveComponent->SetupAttachment(RootComponent);
}


