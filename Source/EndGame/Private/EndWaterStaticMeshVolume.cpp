#include "EndWaterStaticMeshVolume.h"

AEndWaterStaticMeshVolume::AEndWaterStaticMeshVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WaterType = EEndWaterType::Default;
    this->BuildType = EWaterNavBuildType::None;
}


