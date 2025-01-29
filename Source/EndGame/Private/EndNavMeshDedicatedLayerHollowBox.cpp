#include "EndNavMeshDedicatedLayerHollowBox.h"
#include "NavAreas/NavArea_Default.h"

AEndNavMeshDedicatedLayerHollowBox::AEndNavMeshDedicatedLayerHollowBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->AreaClass = UNavArea_Default::StaticClass();
}


