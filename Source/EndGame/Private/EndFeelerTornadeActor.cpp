#include "EndFeelerTornadeActor.h"
#include "Components/SplineComponent.h"

AEndFeelerTornadeActor::AEndFeelerTornadeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InstanceCount = 30;
    this->LineCount = 3;
    this->ActorMovementApplyRate = 0.00f;
    this->RandomSeed = 0;
    this->VerticalHeightOffsetSize = 0.00f;
    this->VerticalHeightOffsetPow = 1.00f;
    this->ExtrusionDistanceMax = 400.00f;
    this->ExtrusionMoveDeltaMax = 100.00f;
    this->ExtrusionDistanceInterpSpeed = 0.10f;
    this->BeginRadius = 100.00f;
    this->HalfRadius = 150.00f;
    this->EndRadius = 100.00f;
    this->LoopCount = 2.00f;
    this->ActivateScaleCurve = NULL;
    this->BeginCenterAnimatedOffset = 0.00f;
    this->BeginCenterAnimatedOffsetLoopTime = 1.00f;
    this->HalfCenterAnimatedOffset = 0.00f;
    this->HalfCenterAnimatedOffsetLoopTime = 1.00f;
    this->EndCenterAnimatedOffset = 0.00f;
    this->EndCenterAnimatedOffsetLoopTime = 1.00f;
    this->BeginCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->HalfCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->EndCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->bInverseMovement = false;
    this->bInverseSplineMovement = false;
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
    this->CullingDeltaHeightMin = 0.00f;
    this->CullingDeltaHeightMax = 0.00f;
    this->bCullingBackSide = true;
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    this->EmissiveColorSettings = NULL;
    this->SplineComponent->SetupAttachment(RootComponent);
}


