#include "SQEXSEADWhizSound.h"
#include "SQEXSEADWhizSeComponent.h"

ASQEXSEADWhizSound::ASQEXSEADWhizSound(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USQEXSEADWhizSeComponent>(TEXT("WhizSeComponent0"));
    this->Sound = NULL;
    this->WhizComponent = (USQEXSEADWhizSeComponent*)RootComponent;
}


