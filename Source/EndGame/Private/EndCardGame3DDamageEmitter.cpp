#include "EndCardGame3DDamageEmitter.h"
#include "Components/SceneComponent.h"

AEndCardGame3DDamageEmitter::AEndCardGame3DDamageEmitter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    this->bPlayer = false;
    this->MoveTime = 0.00f;
}


