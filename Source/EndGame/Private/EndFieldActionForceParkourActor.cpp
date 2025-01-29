#include "EndFieldActionForceParkourActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionForceParkourActor::AEndFieldActionForceParkourActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->UseNaviLinkNum = 1;
    this->bBothWay = true;
    this->bDisableIgnorePublicParkourLinkBox = false;
    this->bDisableUsePC = false;
    this->OverrideWaterDiveEffect = NULL;
    this->TikableVolume->SetupAttachment(RootComponent);
}


