#include "EndNavModifierAdditionalLayerVolume.h"
#include "EndNavAreaAddAttribute.h"

AEndNavModifierAdditionalLayerVolume::AEndNavModifierAdditionalLayerVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaAddAttribute::StaticClass();
    this->LayerType = EEndNavLayerType::Normal;
    this->bCreateNav = false;
}


