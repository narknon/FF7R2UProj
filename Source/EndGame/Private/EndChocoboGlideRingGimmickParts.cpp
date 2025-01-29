#include "EndChocoboGlideRingGimmickParts.h"
#include "Components/SceneComponent.h"

AEndChocoboGlideRingGimmickParts::AEndChocoboGlideRingGimmickParts(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


