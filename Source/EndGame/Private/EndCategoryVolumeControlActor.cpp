#include "EndCategoryVolumeControlActor.h"
#include "EndCategoryVolumeControlComponent.h"

AEndCategoryVolumeControlActor::AEndCategoryVolumeControlActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndCategoryVolumeControlComponent>(TEXT("EndCategoryVolumeControlComponent"));
    this->ControllerComponent = (UEndCategoryVolumeControlComponent*)RootComponent;
}


