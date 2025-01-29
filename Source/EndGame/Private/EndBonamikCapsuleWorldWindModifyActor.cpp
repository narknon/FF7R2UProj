#include "EndBonamikCapsuleWorldWindModifyActor.h"
#include "EndBonamikCapsuleWorldWindModifyComponent.h"

AEndBonamikCapsuleWorldWindModifyActor::AEndBonamikCapsuleWorldWindModifyActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBonamikCapsuleWorldWindModifyComponent>(TEXT("CapsuleWorldWindModify"));
    this->WorldWindModifyComponent = (UEndBonamikCapsuleWorldWindModifyComponent*)RootComponent;
}


