#include "EndFeelerConflictActor.h"
#include "Components/SplineComponent.h"

AEndFeelerConflictActor::AEndFeelerConflictActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SlaveInstanceCount = 30;
    this->LineCount = 1;
    this->RandomSeed = 0;
    this->BeginCenterAnimatedOffset = 0.00f;
    this->BeginCenterAnimatedOffsetLoopTime = 1.00f;
    this->HalfCenterAnimatedOffset = 0.00f;
    this->HalfCenterAnimatedOffsetLoopTime = 1.00f;
    this->EndCenterAnimatedOffset = 0.00f;
    this->EndCenterAnimatedOffsetLoopTime = 1.00f;
    this->BeginCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->HalfCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->EndCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->InstanceFadeTime = 0.20f;
    this->InstanceFadeTimeRate = 0.00f;
    this->LoseFadeOutTime = 0.50f;
    this->LoseFadeOutWaitTime = 0.50f;
    this->LoseStopTime = 1.00f;
    this->SkeletalMeshA = NULL;
    this->SkeletalMeshB = NULL;
    this->AnimationVariationCount = 1;
    this->WinRate = 0.50f;
    this->ConflictRadius = 30.00f;
    this->ConflictBrakeVelocityRate = 0.50f;
    this->ConflictAdditiveVelocityRate = 0.50f;
    this->bAvoidCamera = false;
    this->AvoidCameraBaseSize = 300.00f;
    this->AvoidCameraInstanceSize = 200.00f;
    this->AvoidCameraOffsetScale = 0.50f;
    this->PerformanceModeReductionRate = 0.60f;
    this->CullingDistance = 30000.00f;
    this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    this->EmissiveColorSettingsA = NULL;
    this->EmissiveColorSettingsB = NULL;
    this->SplineComponent->SetupAttachment(RootComponent);
}


