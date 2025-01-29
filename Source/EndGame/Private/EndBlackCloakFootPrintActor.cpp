#include "EndBlackCloakFootPrintActor.h"
#include "Components/SceneComponent.h"

AEndBlackCloakFootPrintActor::AEndBlackCloakFootPrintActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->BPInfo = NULL;
}


