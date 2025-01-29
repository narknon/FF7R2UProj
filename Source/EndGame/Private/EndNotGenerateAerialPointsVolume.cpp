#include "EndNotGenerateAerialPointsVolume.h"
#include "Components/BoxComponent.h"

AEndNotGenerateAerialPointsVolume::AEndNotGenerateAerialPointsVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}


