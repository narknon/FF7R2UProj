#include "EndPBDSphereCollisionActor.h"
#include "Components/SphereComponent.h"

AEndPBDSphereCollisionActor::AEndPBDSphereCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PBDCollisionComponent"));
    this->CollisionComponent = (USphereComponent*)RootComponent;
}


