#include "EndPBDBoxCollisionActor.h"
#include "Components/BoxComponent.h"

AEndPBDBoxCollisionActor::AEndPBDBoxCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("PBDCollisionComponent"));
    this->CollisionComponent = (UBoxComponent*)RootComponent;
}


