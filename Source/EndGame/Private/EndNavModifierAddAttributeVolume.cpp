#include "EndNavModifierAddAttributeVolume.h"
#include "EndNavAreaAddAttribute.h"

AEndNavModifierAddAttributeVolume::AEndNavModifierAddAttributeVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaAddAttribute::StaticClass();
}


