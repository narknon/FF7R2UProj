#include "EndFeelerLaserActor.h"

AEndFeelerLaserActor::AEndFeelerLaserActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SlaveInstanceCount = 30;
    this->LineCount = 1;
    this->ActorMovementApplyRate = 0.00f;
    this->RandomSeed = 0;
    this->MovementDistance = 0.00f;
    this->BeginCenterAnimatedOffset = 0.00f;
    this->BeginCenterAnimatedOffsetLoopTime = 1.00f;
    this->HalfCenterAnimatedOffset = 0.00f;
    this->HalfCenterAnimatedOffsetLoopTime = 1.00f;
    this->EndCenterAnimatedOffset = 0.00f;
    this->EndCenterAnimatedOffsetLoopTime = 1.00f;
    this->BeginCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->HalfCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->EndCenterAnimatedOffsetLoopTimeRate = 0.00f;
    this->bUseInstancedStaticMesh = false;
    this->SkeletalMesh = NULL;
    this->StaticMesh = NULL;
    this->AnimationVariationCount = 1;
    this->PerformanceModeReductionRate = 0.60f;
    this->CullingDistance = 30000.00f;
    this->EmissiveColorSettings = NULL;
}


