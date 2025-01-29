#include "EndFieldMineCartRailComponent.h"
#include "EndFieldMineCartSplineComponent.h"

UEndFieldMineCartRailComponent::UEndFieldMineCartRailComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SplineComponent = CreateDefaultSubobject<UEndFieldMineCartSplineComponent>(TEXT("Rail"));
    this->bPullLimitIsKeepCharaSpace = false;
    this->bPushLimitIsKeepCharaSpace = false;
}


