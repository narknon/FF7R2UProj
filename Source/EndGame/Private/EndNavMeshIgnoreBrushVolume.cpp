#include "EndNavMeshIgnoreBrushVolume.h"

AEndNavMeshIgnoreBrushVolume::AEndNavMeshIgnoreBrushVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->bLevelBounds = false;
}


