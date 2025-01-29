#include "EndChocoboRaceSpline.h"
#include "Components/SceneComponent.h"
#include "EndChocoboRaceSplineComponent.h"

AEndChocoboRaceSpline::AEndChocoboRaceSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->SplineComponent = CreateDefaultSubobject<UEndChocoboRaceSplineComponent>(TEXT("ChocoboRaceSplineComponent"));
    this->NextMainCourseSpline = NULL;
    this->NextSubCourseSpline = NULL;
    this->SplineComponent->SetupAttachment(RootComponent);
}


