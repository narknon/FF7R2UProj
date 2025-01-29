#include "EndDynamicBodyCollisionActor.h"
#include "Components/SceneComponent.h"

AEndDynamicBodyCollisionActor::AEndDynamicBodyCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NAME_RootComp"));
}


