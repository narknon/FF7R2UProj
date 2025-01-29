#include "EndPBDIgnoreCollisionActor.h"
#include "EndPBDIgnoreCollisionComponent.h"

AEndPBDIgnoreCollisionActor::AEndPBDIgnoreCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndPBDIgnoreCollisionComponent>(TEXT("PBDIgnoreCollisionComponent"));
    this->IgnoreCollisionComponent = (UEndPBDIgnoreCollisionComponent*)RootComponent;
}


