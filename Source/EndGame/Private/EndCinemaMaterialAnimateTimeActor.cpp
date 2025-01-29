#include "EndCinemaMaterialAnimateTimeActor.h"
#include "EndCinemaMaterialAnimateTimeComponent.h"

AEndCinemaMaterialAnimateTimeActor::AEndCinemaMaterialAnimateTimeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndCinemaMaterialAnimateTimeComponent>(TEXT("EndCinemaMaterialAnimateTimeComponent"));
    this->ControllerComponent = (UEndCinemaMaterialAnimateTimeComponent*)RootComponent;
}


