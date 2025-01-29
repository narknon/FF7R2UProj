#include "EndDolphinJumpSplineActor.h"
#include "Components/SceneComponent.h"
#include "EndDolphinJumpSplineComponent.h"

AEndDolphinJumpSplineActor::AEndDolphinJumpSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    this->SplineComponent = CreateDefaultSubobject<UEndDolphinJumpSplineComponent>(TEXT("SplineComponent"));
    this->SplineComponent->SetupAttachment(RootComponent);
}


