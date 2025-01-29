#include "EndFieldActionMovingWalkWayActor.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndFieldMovingWalkwaySplineComponent.h"

AEndFieldActionMovingWalkWayActor::AEndFieldActionMovingWalkWayActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->MovingPath = CreateDefaultSubobject<UEndFieldMovingWalkwaySplineComponent>(TEXT("MovingPathComponent"));
    this->bEnableWalkwayLimitMove = true;
    this->MovingPath->SetupAttachment(RootComponent);
    this->TikableVolume->SetupAttachment(RootComponent);
}


