#include "EndFeelerBarrierActor.h"
#include "Components/SplineComponent.h"

AEndFeelerBarrierActor::AEndFeelerBarrierActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InstanceCount = 30;
    this->LineCount = 3;
    this->RandomSeed = 0;
    this->VerticalHeightOffsetSize = 0.00f;
    this->VerticalHeightOffsetPow = 1.00f;
    this->ExtrusionDistanceMax = 400.00f;
    this->ExtrusionMoveDeltaMax = 100.00f;
    this->ExtrusionDistanceInterpSpeed = 0.10f;
    this->bInverseMovement = false;
    this->ActivateSpeedScaleCurve = NULL;
    this->ActivateTranslationScaleCurve = NULL;
    this->bUseInstancedStaticMesh = false;
    this->SkeletalMesh = NULL;
    this->StaticMesh = NULL;
    this->AnimationVariationCount = 1;
    this->bAvoidCamera = false;
    this->AvoidCameraBaseSize = 300.00f;
    this->AvoidCameraInstanceSize = 200.00f;
    this->AvoidCameraOffsetScale = 0.50f;
    this->PerformanceModeReductionRate = 0.60f;
    this->CullingDistance = 30000.00f;
    this->SplinePointCount = 8;
    this->SplinePointRadius = 1500.00f;
    this->bRefreshSpline = true;
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    this->EmissiveColorSettings = NULL;
    this->SplineComponent->SetupAttachment(RootComponent);
}


