#include "EndSimpleShootingTargetVolume.h"
#include "EndFieldActionShootingTargetComponent.h"

AEndSimpleShootingTargetVolume::AEndSimpleShootingTargetVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ShootingTargetComponent = CreateDefaultSubobject<UEndFieldActionShootingTargetComponent>(TEXT("ShootingTargetComponent"));
    this->ShootingTargetComponent->SetupAttachment(RootComponent);
}


