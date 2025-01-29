#include "EndShootingGameResultSplineActor.h"
#include "Components/SceneComponent.h"
#include "EndShootingGameSplineComponent.h"

AEndShootingGameResultSplineActor::AEndShootingGameResultSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->SplineComponent = CreateDefaultSubobject<UEndShootingGameSplineComponent>(TEXT("SplineComponent"));
    this->MotionType = ETargetResultMotionType::Joy1;
    this->SplineComponent->SetupAttachment(RootComponent);
}


