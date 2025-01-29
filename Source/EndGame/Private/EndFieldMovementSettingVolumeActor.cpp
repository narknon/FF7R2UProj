#include "EndFieldMovementSettingVolumeActor.h"
#include "EndFieldMovementSettingVolumeComponent.h"

AEndFieldMovementSettingVolumeActor::AEndFieldMovementSettingVolumeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SettingVolume = CreateDefaultSubobject<UEndFieldMovementSettingVolumeComponent>(TEXT("SettingVolume"));
}


