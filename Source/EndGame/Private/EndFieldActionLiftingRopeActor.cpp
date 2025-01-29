#include "EndFieldActionLiftingRopeActor.h"
#include "EndFieldActionTriggerCustomComponent.h"

AEndFieldActionLiftingRopeActor::AEndFieldActionLiftingRopeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->MoveType = ELiftingRopeActorMoveType::UpperToLower;
    this->LowerEnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("LowerEnterVolume"));
    this->UpperEnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("UpperEnterVolume"));
    this->LeaveAngle = 0.00f;
    this->LowerEnterVolume->SetupAttachment(RootComponent);
    this->UpperEnterVolume->SetupAttachment(RootComponent);
}


