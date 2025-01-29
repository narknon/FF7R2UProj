#include "EndFieldActionChocoboJumpStandActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionChocoboJumpStandActor::AEndFieldActionChocoboJumpStandActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("EnterVolume"));
    this->EnableJumpAngleRange = 30.00f;
    this->bOverrideJumpGravityScale = false;
    this->bOverrideJumpVelocityZ = false;
    this->bOverrideJumpVelocityXY = false;
    this->JumpGravityScale = 7.00f;
    this->JumpVelocityZ = 1800.00f;
    this->JumpVelocityXY = 1500.00f;
    this->EnterVolume->SetupAttachment(RootComponent);
}


