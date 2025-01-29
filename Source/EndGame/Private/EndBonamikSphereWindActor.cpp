#include "EndBonamikSphereWindActor.h"
#include "EndBonamikSphereWindComponent.h"

AEndBonamikSphereWindActor::AEndBonamikSphereWindActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBonamikSphereWindComponent>(TEXT("SphereWind"));
    this->WindComponent = (UEndBonamikSphereWindComponent*)RootComponent;
}


