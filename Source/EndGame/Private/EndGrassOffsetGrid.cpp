#include "EndGrassOffsetGrid.h"
#include "Components/SceneComponent.h"

AEndGrassOffsetGrid::AEndGrassOffsetGrid(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->UnitLength = 100.00f;
    this->GridNumX = 100;
    this->GridNumY = 100;
    this->GridNumZ = 20;
    this->TreeLevel_ = 0;
}


