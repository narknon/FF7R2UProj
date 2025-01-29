#include "EndFieldActionActorPoleSlider.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionActorPoleSlider::AEndFieldActionActorPoleSlider(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->LowerVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("LowerVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->LeaveAngle = 0.00f;
    this->LowerVolume->SetupAttachment(RootComponent);
    this->UpperVolume->SetupAttachment(RootComponent);
}


