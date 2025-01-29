#include "EndNaviMapVolume.h"

AEndNaviMapVolume::AEndNaviMapVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->LayerNumber = EEndNaviMapLayer::Layer_00;
    this->OpenGroupNumber = EEndNaviMapOpenGroup::OpenGroup_None;
    this->VisitGroupNumber = EEndNaviMapVisitGroup::VisitGroup_None;
    this->UniqueIndexOffset = EEndNaviMapUniqueIndexOffset::Offset_0;
    this->CaptureGroup = 0;
    this->bIgnoreOverlap = false;
    this->bIgnoreGenetateTexture = false;
    this->bUsedByGridVolume = false;
    this->UniqueIndex = -1;
}


