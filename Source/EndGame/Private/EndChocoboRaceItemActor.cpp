#include "EndChocoboRaceItemActor.h"
#include "Components/SceneComponent.h"

AEndChocoboRaceItemActor::AEndChocoboRaceItemActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->ItemType = EEndChocoboRaceItemType::DashStock;
    this->ItemClass = NULL;
    this->RespawnIntervalByPlayer = 40.00f;
    this->RespawnIntervalByNpc = 15.00f;
}


