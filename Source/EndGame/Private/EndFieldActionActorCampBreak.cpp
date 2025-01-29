#include "EndFieldActionActorCampBreak.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorCampBreak::AEndFieldActionActorCampBreak(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->CampStartMenuActionName = TEXT("actCmn_Camp");
    this->TickableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TickableVolume"));
    this->TickableVolume->SetupAttachment(RootComponent);
}


