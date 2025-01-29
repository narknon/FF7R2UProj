#include "EndFieldActionActorSimpleInteract.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorSimpleInteract::AEndFieldActionActorSimpleInteract(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableAreaVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableAreaVolume"));
    this->StateAction = NULL;
    this->TikableAreaVolume->SetupAttachment(RootComponent);
}


