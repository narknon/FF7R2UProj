#include "EndBonamikBoxWorldWindModifyActor.h"
#include "EndBonamikBoxWorldWindModifyComponent.h"

AEndBonamikBoxWorldWindModifyActor::AEndBonamikBoxWorldWindModifyActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBonamikBoxWorldWindModifyComponent>(TEXT("BoxWorldWindModify"));
    this->WorldWindModifyComponent = (UEndBonamikBoxWorldWindModifyComponent*)RootComponent;
}


