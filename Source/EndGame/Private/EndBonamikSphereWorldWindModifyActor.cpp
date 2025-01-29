#include "EndBonamikSphereWorldWindModifyActor.h"
#include "EndBonamikSphereWorldWindModifyComponent.h"

AEndBonamikSphereWorldWindModifyActor::AEndBonamikSphereWorldWindModifyActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndBonamikSphereWorldWindModifyComponent>(TEXT("SphereWorldWindModify"));
    this->WorldWindModifyComponent = (UEndBonamikSphereWorldWindModifyComponent*)RootComponent;
}


