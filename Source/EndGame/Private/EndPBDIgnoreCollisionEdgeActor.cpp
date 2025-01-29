#include "EndPBDIgnoreCollisionEdgeActor.h"
#include "EndPBDIgnoreCollisionEdgeComponent.h"

AEndPBDIgnoreCollisionEdgeActor::AEndPBDIgnoreCollisionEdgeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndPBDIgnoreCollisionEdgeComponent>(TEXT("PBDIgnoreCollisionEdgeComponent"));
    this->IgnoreCollisionEdgeComponent = (UEndPBDIgnoreCollisionEdgeComponent*)RootComponent;
}


