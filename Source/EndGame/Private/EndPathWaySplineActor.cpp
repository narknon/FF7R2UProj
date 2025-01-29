#include "EndPathWaySplineActor.h"
#include "Components/SplineComponent.h"

AEndPathWaySplineActor::AEndPathWaySplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PathWayBaseWidth = 100.00f;
    this->PathWayOffsetWidth = 0.00f;
    this->PathWaySpace = 10.00f;
    this->ArrowLength = 100.00f;
    this->ArrowSize = 20.00f;
    this->ArrowThickness = 5.00f;
    this->PathWayComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}


