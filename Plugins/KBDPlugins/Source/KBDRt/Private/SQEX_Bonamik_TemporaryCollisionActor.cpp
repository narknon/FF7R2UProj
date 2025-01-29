#include "SQEX_Bonamik_TemporaryCollisionActor.h"
#include "Components/SceneComponent.h"

ASQEX_Bonamik_TemporaryCollisionActor::ASQEX_Bonamik_TemporaryCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}


