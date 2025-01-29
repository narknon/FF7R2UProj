#include "EndWaterVolume.h"
#include "EndNavAreaWater.h"

AEndWaterVolume::AEndWaterVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bWaterVolume = true;
    this->WaterType = EEndWaterType::Default;
    this->BuildType = EWaterNavBuildType::None;
    this->AreaClass = UEndNavAreaWater::StaticClass();
}


