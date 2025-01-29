#include "EndFieldActionRedHoldDeliveryActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionRedHoldDeliveryActor::AEndFieldActionRedHoldDeliveryActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->RedHoldDeliveryVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("RedHoldDeliveryVolume"));
    this->DeliveryObjectClass = NULL;
    this->RedHoldDeliveryVolume->SetupAttachment(RootComponent);
}


