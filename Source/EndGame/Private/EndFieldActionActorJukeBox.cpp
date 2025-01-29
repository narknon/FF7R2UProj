#include "EndFieldActionActorJukeBox.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionActorJukeBox::AEndFieldActionActorJukeBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->InterestRadius = 300.00f;
    this->PressVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->Party01BoxComponent = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("Party01BoxComponent"));
    this->Party02BoxComponent = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("Party02BoxComponent"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->Party01BoxComponent->SetupAttachment(RootComponent);
    this->Party02BoxComponent->SetupAttachment(RootComponent);
    this->PressVolume->SetupAttachment(RootComponent);
}


