#include "EndSplineActorBase.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

AEndSplineActorBase::AEndSplineActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->SplineMoveComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineMoveComponent"));
    this->IsLoop = false;
    this->SplineMoveComponent->SetupAttachment(RootComponent);
}


