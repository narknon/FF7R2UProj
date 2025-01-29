#include "EndNavMeshIgnoreBoxVolume.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "EndNavModifierComponent.h"

AEndNavMeshIgnoreBoxVolume::AEndNavMeshIgnoreBoxVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->AreaClass = NULL;
    this->BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("ModifierVolume"));
    this->BoxComponent->SetupAttachment(RootComponent);
}


