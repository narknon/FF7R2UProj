#include "EndMobCrowdActor.h"

AEndMobCrowdActor::AEndMobCrowdActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bUseMinLOD = true;
    this->MinLOD = 4;
    this->bForceCastShadow = false;
    this->PerformanceModeReductionRate = 0.00f;
    this->CameraCutCullingDistance = 0.00f;
    this->UpdateLODDistanceThresholds.AddDefaulted(3);
    this->GraphicsModeUpdateLODDistanceBias = 1.30f;
}

void AEndMobCrowdActor::Stop(float BlendTime, bool bUseFade) {
}

void AEndMobCrowdActor::SetSkeletalMeshVisibility(int32 Index, bool bVisiblity) {
}

void AEndMobCrowdActor::SetOverride(FName OverrideName) {
}

void AEndMobCrowdActor::SetCustomSkeletalMesh(int32 Index, AEndCharacterBase* Character) {
}

void AEndMobCrowdActor::ResetOverride() {
}

void AEndMobCrowdActor::Play(float BlendTime, bool bUseFade) {
}

void AEndMobCrowdActor::OnRefleshCustomSkeletalMesh() {
}


