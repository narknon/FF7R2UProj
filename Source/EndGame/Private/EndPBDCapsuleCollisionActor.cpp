#include "EndPBDCapsuleCollisionActor.h"
#include "Components/CapsuleComponent.h"

AEndPBDCapsuleCollisionActor::AEndPBDCapsuleCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PBDCollisionComponent"));
    this->CollisionComponent = (UCapsuleComponent*)RootComponent;
}


