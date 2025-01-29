#include "EndNavModifierFootBGMVolume.h"
#include "EndNavAreaAddAttribute.h"

AEndNavModifierFootBGMVolume::AEndNavModifierFootBGMVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaAddAttribute::StaticClass();
}


