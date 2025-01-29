#include "EndChocoboJetOneWayGuideActor.h"
#include "EndChocoboJetOneWayGuideSplineComponent.h"

AEndChocoboJetOneWayGuideActor::AEndChocoboJetOneWayGuideActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndChocoboJetOneWayGuideSplineComponent>(TEXT("EndChocoboJetOneWayGuideSplineComponent"));
    this->TimeOut = 5.00f;
    this->SplineComponent = (UEndChocoboJetOneWayGuideSplineComponent*)RootComponent;
}


