#include "EndNavMeshAttributeOnlyVolume.h"
#include "NavAreas/NavArea_Default.h"

AEndNavMeshAttributeOnlyVolume::AEndNavMeshAttributeOnlyVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->AreaClass = UNavArea_Default::StaticClass();
}


