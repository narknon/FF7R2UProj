#include "EndFieldActionSaveActorBase.h"
#include "EndNavModifierComponent.h"

AEndFieldActionSaveActorBase::AEndFieldActionSaveActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
}


