#include "EndPlayerTrigger.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

AEndPlayerTrigger::AEndPlayerTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    this->CapsuleComponent->SetupAttachment(RootComponent);
}


