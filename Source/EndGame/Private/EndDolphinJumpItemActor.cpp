#include "EndDolphinJumpItemActor.h"
#include "EndDolphinJumpOceanFloaterComponent.h"

AEndDolphinJumpItemActor::AEndDolphinJumpItemActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->OceanFloaterComponent = CreateDefaultSubobject<UEndDolphinJumpOceanFloaterComponent>(TEXT("Floater"));
    this->OceanFloaterComponent->SetupAttachment(RootComponent);
}


