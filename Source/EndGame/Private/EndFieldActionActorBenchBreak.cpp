#include "EndFieldActionActorBenchBreak.h"
#include "Components/StaticMeshComponent.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionActorBenchBreak::AEndFieldActionActorBenchBreak(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->CustomFadeTime = -1.00f;
    this->PressVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("PressVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->BenchMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BenchMesh"));
    this->ZabutonActorClass = NULL;
    this->BenchMeshComponent->SetupAttachment(RootComponent);
    this->PressVolume->SetupAttachment(RootComponent);
}


