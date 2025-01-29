#include "EndNavBlockingModifierVolume.h"
#include "EndAerialIgnoreComponent.h"

AEndNavBlockingModifierVolume::AEndNavBlockingModifierVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->IsFirstStart = true;
    this->AerialIgnoreComponent = CreateDefaultSubobject<UEndAerialIgnoreComponent>(TEXT("EndAerialIgnoreComponent"));
    this->CanEverAerial = true;
    this->AerialIgnoreComponent->SetupAttachment(RootComponent);
}


