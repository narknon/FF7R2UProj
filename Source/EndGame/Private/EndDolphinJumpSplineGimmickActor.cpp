#include "EndDolphinJumpSplineGimmickActor.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

AEndDolphinJumpSplineGimmickActor::AEndDolphinJumpSplineGimmickActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    this->SplineMoveComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SplineMoveComponent"));
    this->StopSeconds = 0.00f;
    this->SplineMoveComponent->SetupAttachment(SplineComponent);
}


