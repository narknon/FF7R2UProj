#include "EndBonamikCapsuleWindActor.h"
#include "EndBonamikCapsuleWindComponent.h"

AEndBonamikCapsuleWindActor::AEndBonamikCapsuleWindActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBonamikCapsuleWindComponent>(TEXT("CapsuleWind"));
    this->WindComponent = (UEndBonamikCapsuleWindComponent*)RootComponent;
}


