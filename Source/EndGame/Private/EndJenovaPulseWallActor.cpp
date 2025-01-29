#include "EndJenovaPulseWallActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"

AEndJenovaPulseWallActor::AEndJenovaPulseWallActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InstanceCount = 30;
    this->LineCount = 3;
    this->RandomSeed = 0;
    this->Height = 0.00f;
    this->Extruct = 0.00f;
    this->ActivateAnimationCurve = NULL;
    this->PulseAnimationCurve = NULL;
    this->PulseGroupCount = 1;
    this->SplinePointCount = 8;
    this->SplinePointRadius = 1500.00f;
    this->bRefreshSpline = true;
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    this->InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Mesh"));
    this->EmissiveColorSettings = NULL;
    this->InstancedMeshComponent->SetupAttachment(RootComponent);
    this->SplineComponent->SetupAttachment(RootComponent);
}


