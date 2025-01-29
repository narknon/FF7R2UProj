#include "EndFieldActionChocoboClimbActor.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionChocoboClimbActor::AEndFieldActionChocoboClimbActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("EnterVolume"));
    this->ExitVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("ExitVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->ClimbNormalAngle = 0.00f;
    this->ClimbCharacterNormalAngle = 20.00f;
    this->EnterVolume->SetupAttachment(RootComponent);
    this->ExitVolume->SetupAttachment(RootComponent);
}


