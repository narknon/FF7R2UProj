#include "EndFieldActionTurnGearActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionTurnGearActor::AEndFieldActionTurnGearActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->TurnAngleMax = 1080.00f;
    this->PlayerMotionSpeedUpStartSec = 1.00f;
    this->PlayerMotionSpeedUpStartToMaxSec = 5.00f;
    this->PlayerMotionSpeedUpMaxRate = 1.50f;
    this->SoundBank_Turning = NULL;
    this->SoundBank_LifeStream = NULL;
    this->TikableVolume->SetupAttachment(RootComponent);
}


