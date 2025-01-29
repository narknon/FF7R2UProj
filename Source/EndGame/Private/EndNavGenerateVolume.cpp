#include "EndNavGenerateVolume.h"
#include "NavAreas/NavArea_Default.h"

AEndNavGenerateVolume::AEndNavGenerateVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UNavArea_Default::StaticClass();
}


