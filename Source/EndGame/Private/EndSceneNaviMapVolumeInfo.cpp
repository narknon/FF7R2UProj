#include "EndSceneNaviMapVolumeInfo.h"

FEndSceneNaviMapVolumeInfo::FEndSceneNaviMapVolumeInfo() {
    this->LayerNumber = EEndNaviMapLayer::Layer_00;
    this->OpenGroupNumber = EEndNaviMapOpenGroup::OpenGroup_None;
    this->VisitGroupNumber = EEndNaviMapVisitGroup::VisitGroup_None;
    this->UniqueIndex = 0;
}

