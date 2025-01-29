#include "EndSkeletalMeshActorBase.h"
#include "EndSkeletalMeshComponent.h"

AEndSkeletalMeshActorBase::AEndSkeletalMeshActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndSkeletalMeshComponent>(TEXT("SkeletalMeshComponent0"))) {
    const FProperty* p_SkeletalMeshComponent = GetClass()->FindPropertyByName("SkeletalMeshComponent");
    (*p_SkeletalMeshComponent->ContainerPtrToValuePtr<USkeletalMeshComponent*>(this)) = (USkeletalMeshComponent*)RootComponent;
    this->MaterialPack = NULL;
    this->EmissiveColorComponent = NULL;
    this->OverrideEmissiveColorSettings = NULL;
    this->LightAnimationComponent = NULL;
    this->CoordinateAnimationComponent = NULL;
    this->FlowMapAnimationComponent = NULL;
    this->DeformMesh = NULL;
    this->DeformAnimationComponent = NULL;
    this->DeformMeshComponent = NULL;
    this->bSteeringObstacle = false;
}

void AEndSkeletalMeshActorBase::StopLightAnimation(FName RequestID) {
}

void AEndSkeletalMeshActorBase::StopFlowMapAnimation() {
}

void AEndSkeletalMeshActorBase::StopEmissiveColorAnimation(FName RequestID) {
}

void AEndSkeletalMeshActorBase::StopDeformAnimation() {
}

void AEndSkeletalMeshActorBase::StopCoordinateAnimation(FName RequestID) {
}

void AEndSkeletalMeshActorBase::SetDirectEmissiveColor(FName RequestID, FName EmissiveColorSettingsId, float IntensityAlpha) {
}

void AEndSkeletalMeshActorBase::ResetDirectEmissiveColor(FName RequestID) {
}

void AEndSkeletalMeshActorBase::PlayLightAnimation(FName RequestID, FName LightAnimationSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset) {
}

void AEndSkeletalMeshActorBase::PlayFlowMapAnimation(float PlayRate, bool bOverrideConstantParameter, const FVector& ConstantParameter0, const FVector& ConstantParameter1) {
}

void AEndSkeletalMeshActorBase::PlayExtraActionFromAsset(UAnimSequenceBase* Asset, bool bLooping, float BlendInTime, float StartTime) {
}

void AEndSkeletalMeshActorBase::PlayEmissiveColorAnimation(FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer) {
}

void AEndSkeletalMeshActorBase::PlayDeformAnimation(EEndDeformAnimationType AnimationType, float StartFrame, const FName& SyncAnimationName, EEndAnimComponentControlLayer Layer) {
}

void AEndSkeletalMeshActorBase::PlayCoordinateAnimation(FName RequestID, FName CoordinateAnimationSettingsId, EEndAnimationCurveType CurveType, bool bLoop, float Duration) {
}

bool AEndSkeletalMeshActorBase::IsActiveLightAnimation() const {
    return false;
}

bool AEndSkeletalMeshActorBase::IsActiveFlowMapAnimation() const {
    return false;
}

bool AEndSkeletalMeshActorBase::IsActiveEmissiveColorAnimation() const {
    return false;
}

bool AEndSkeletalMeshActorBase::IsActiveDeformAnimation() const {
    return false;
}

bool AEndSkeletalMeshActorBase::IsActiveCoordinateAnimation() const {
    return false;
}


