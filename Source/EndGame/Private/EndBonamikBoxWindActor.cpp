#include "EndBonamikBoxWindActor.h"
#include "EndBonamikBoxWindComponent.h"

AEndBonamikBoxWindActor::AEndBonamikBoxWindActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBonamikBoxWindComponent>(TEXT("BoxWind"));
    this->WindComponent = (UEndBonamikBoxWindComponent*)RootComponent;
}


