#include "EndChocoboGlideGimmickSplineActorBase.h"
#include "EndChocoboGlideGimmickSplineComponent.h"

AEndChocoboGlideGimmickSplineActorBase::AEndChocoboGlideGimmickSplineActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndChocoboGlideGimmickSplineComponent>(TEXT("SplineComponent"));
    this->GimmickSplineComponent = (UEndChocoboGlideGimmickSplineComponent*)RootComponent;
    this->bEnableMove = false;
}


