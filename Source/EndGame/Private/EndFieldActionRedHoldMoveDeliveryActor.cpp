#include "EndFieldActionRedHoldMoveDeliveryActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionRedHoldMoveDeliveryActor::AEndFieldActionRedHoldMoveDeliveryActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->RedHoldMoveDeliveryVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("RedHoldMoveDeliveryVolume"));
    this->DeliveryObjectClass = NULL;
    this->GoalPointVibrationRadius = 1000.00f;
    this->bGoalPointFixPutDir = false;
    this->GoalPointFixPutDirOffset = 0.00f;
    this->bDeliveryIsHook = false;
    this->DeliverySuccessNum = 1;
    this->RedHoldMoveDeliveryVolume->SetupAttachment(RootComponent);
}


