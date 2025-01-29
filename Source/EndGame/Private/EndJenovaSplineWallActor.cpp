#include "EndJenovaSplineWallActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"

AEndJenovaSplineWallActor::AEndJenovaSplineWallActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RandomSeed = 0;
    this->PlacementOffset = 0.00f;
    this->Roll = 0.00f;
    this->ActivateAnimationCurve = NULL;
    this->ActivateRotationCurve = NULL;
    this->SplinePointCount = 8;
    this->SplinePointRadius = 1500.00f;
    this->SplinePointLoopCount = 1.00f;
    this->SplinePointHeight = 1500.00f;
    this->bRefreshSpline = true;
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    this->InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Mesh"));
    this->EmissiveColorSettings = NULL;
    this->InstancedMeshComponent->SetupAttachment(RootComponent);
    this->SplineComponent->SetupAttachment(RootComponent);
}


