#include "EndTinyBroncoDolphinAreaSplineActor.h"
#include "EndTinyBroncoDolphinAreaSplineComponent.h"

AEndTinyBroncoDolphinAreaSplineActor::AEndTinyBroncoDolphinAreaSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndTinyBroncoDolphinAreaSplineComponent>(TEXT("EndTinyBroncoDolphinAreaSplineComponent"));
    this->NextLotterySubtractTime = 1.00f;
    this->CoolDownTime = 10.00f;
    this->Priority = 0;
    this->MaxEventNum = 10;
    this->SplineComponent = (UEndTinyBroncoDolphinAreaSplineComponent*)RootComponent;
}


