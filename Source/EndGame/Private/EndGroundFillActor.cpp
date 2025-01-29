#include "EndGroundFillActor.h"
#include "Components/SceneComponent.h"

AEndGroundFillActor::AEndGroundFillActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->bBuild = false;
    this->bFillDisableScale = true;
    this->FillScatterScale = 0.62f;
    this->bDebugDisableEdgePass = false;
    this->bDebugDisableFinalPass = false;
    this->bDebugLineBatch = false;
    this->bDebugRenderTarget = false;
    this->bDebugInstanceColor = false;
    this->bDebugMeshTypeColor = false;
    this->FillType = NULL;
    this->SourceMeshComponent = NULL;
    this->DebugLineBatchComponent = NULL;
    this->DebugPlaneMeshComponent = NULL;
    this->DebugPlaneMID = NULL;
}


