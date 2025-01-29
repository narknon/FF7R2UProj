#include "EndChocoboRaceSubSpline.h"
#include "Components/SceneComponent.h"
#include "EndChocoboRaceSplineComponent.h"

AEndChocoboRaceSubSpline::AEndChocoboRaceSubSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->SplineComponent = CreateDefaultSubobject<UEndChocoboRaceSplineComponent>(TEXT("ChocoboRaceSplineComponent"));
    this->Probability = 20.00f;
    this->Capacity = 2;
    this->SplineComponent->SetupAttachment(RootComponent);
}


