#include "EndAerialIgnoreVolume.h"
#include "EndAerialIgnoreComponent.h"

AEndAerialIgnoreVolume::AEndAerialIgnoreVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AerialIgnoreComponent = CreateDefaultSubobject<UEndAerialIgnoreComponent>(TEXT("EndAerialIgnoreComponent"));
}


