#include "EndChocoboRaceGimmickSplineActorBase.h"
#include "Components/SplineComponent.h"

AEndChocoboRaceGimmickSplineActorBase::AEndChocoboRaceGimmickSplineActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    this->GimmickSplineComponent = (USplineComponent*)RootComponent;
    this->MoveSpeed = 10.00f;
}


