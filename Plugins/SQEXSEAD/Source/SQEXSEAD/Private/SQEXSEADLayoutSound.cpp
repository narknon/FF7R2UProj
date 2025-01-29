#include "SQEXSEADLayoutSound.h"
#include "SQEXSEADLayoutComponent.h"

ASQEXSEADLayoutSound::ASQEXSEADLayoutSound(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USQEXSEADLayoutComponent>(TEXT("LayoutComponent0"));
    this->LayoutComponent = (USQEXSEADLayoutComponent*)RootComponent;
    this->bSyncActorHidden = true;
}


