#include "EndFieldActionDamageReciveVolume.h"
#include "EndFieldActionDamageReciveComponent.h"

AEndFieldActionDamageReciveVolume::AEndFieldActionDamageReciveVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DamageReciveComponent = CreateDefaultSubobject<UEndFieldActionDamageReciveComponent>(TEXT("DamageReciveComponent"));
    this->DamageReciveComponent->SetupAttachment(RootComponent);
}


