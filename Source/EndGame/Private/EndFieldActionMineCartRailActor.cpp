#include "EndFieldActionMineCartRailActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionMineCartRailActor::AEndFieldActionMineCartRailActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->MineCartVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("MineCartVolume"));
    this->MineCartVolume->SetupAttachment(RootComponent);
}


