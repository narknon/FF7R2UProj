#include "EndFieldVaultActionLineActor.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndFieldVaultActionLineComponent.h"

AEndFieldVaultActionLineActor::AEndFieldVaultActionLineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->SplineMoveComponent = CreateDefaultSubobject<UEndFieldVaultActionLineComponent>(TEXT("UEndFieldVaultActionLineComponent"));
    this->UpperVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("UpperVolume"));
    this->SplineMoveComponent->SetupAttachment(RootComponent);
    this->UpperVolume->SetupAttachment(RootComponent);
}


