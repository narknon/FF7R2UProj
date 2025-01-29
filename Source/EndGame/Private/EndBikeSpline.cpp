#include "EndBikeSpline.h"
#include "Components/SceneComponent.h"
#include "EndBikeSplineComponent.h"

AEndBikeSpline::AEndBikeSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->mSplineComponent = CreateDefaultSubobject<UEndBikeSplineComponent>(TEXT("BikeSplineComponent"));
    this->mSplineComponent->SetupAttachment(RootComponent);
}


