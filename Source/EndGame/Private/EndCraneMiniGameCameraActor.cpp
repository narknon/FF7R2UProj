#include "EndCraneMiniGameCameraActor.h"
#include "Components/SplineComponent.h"

AEndCraneMiniGameCameraActor::AEndCraneMiniGameCameraActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    this->SplineComponent->SetupAttachment(RootComponent);
}


