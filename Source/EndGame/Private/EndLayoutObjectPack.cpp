#include "EndLayoutObjectPack.h"
#include "Components/SceneComponent.h"

AEndLayoutObjectPack::AEndLayoutObjectPack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}


