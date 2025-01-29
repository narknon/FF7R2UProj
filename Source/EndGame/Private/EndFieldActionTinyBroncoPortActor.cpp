#include "EndFieldActionTinyBroncoPortActor.h"
#include "Components/SphereComponent.h"

AEndFieldActionTinyBroncoPortActor::AEndFieldActionTinyBroncoPortActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->OverlapVolume = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapVolume"));
    this->PortEffect = NULL;
    this->InteractionRadius = 5000.00f;
    this->IconInputSuccessTime = 3.00f;
    this->OverlapVolume->SetupAttachment(RootComponent);
}


