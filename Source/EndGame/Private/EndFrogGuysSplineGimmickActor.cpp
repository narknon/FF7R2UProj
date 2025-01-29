#include "EndFrogGuysSplineGimmickActor.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

AEndFrogGuysSplineGimmickActor::AEndFrogGuysSplineGimmickActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    this->SplineMoveComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SplineMoveComponent"));
    this->SplineMoveSpeed = 100.00f;
    this->SplineStopTime = 5.00f;
    this->SplineMoveStartState = EEndFrogGuysSplineMoveState::MoveForward;
    this->SplineMoveStartTime = 0.00f;
    this->SplineComponent->SetupAttachment(RootComponent);
    this->SplineMoveComponent->SetupAttachment(SplineComponent);
}


