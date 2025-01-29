#include "EndNavMeshIgnoreStaticMeshVolume.h"
#include "Components/StaticMeshComponent.h"
#include "NavAreas/NavArea_Null.h"

AEndNavMeshIgnoreStaticMeshVolume::AEndNavMeshIgnoreStaticMeshVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->AreaClass = UNavArea_Null::StaticClass();
    this->StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    this->StaticMesh = NULL;
}


