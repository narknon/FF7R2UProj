#include "EndCinemaWidgetControlActor.h"
#include "EndCinemaWidgetControlComponent.h"

AEndCinemaWidgetControlActor::AEndCinemaWidgetControlActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndCinemaWidgetControlComponent>(TEXT("EndCinemaWidgetControlComponent"));
    this->ControllerComponent = (UEndCinemaWidgetControlComponent*)RootComponent;
}


