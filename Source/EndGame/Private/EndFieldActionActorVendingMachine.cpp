#include "EndFieldActionActorVendingMachine.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionActorVendingMachine::AEndFieldActionActorVendingMachine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->PressVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->PressVolume->SetupAttachment(RootComponent);
}


