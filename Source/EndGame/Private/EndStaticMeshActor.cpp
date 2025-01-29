#include "EndStaticMeshActor.h"

AEndStaticMeshActor::AEndStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MaterialPack = NULL;
    this->EmissiveColorComponent = NULL;
    this->OverrideEmissiveColorSettings = NULL;
}

void AEndStaticMeshActor::StopEmissiveColorAnimation(FName RequestID) {
}

void AEndStaticMeshActor::SetDirectEmissiveColor(FName RequestID, FName EmissiveColorSettingsId, float IntensityAlpha) {
}

void AEndStaticMeshActor::ResetDirectEmissiveColor(FName RequestID) {
}

void AEndStaticMeshActor::PlayEmissiveColorAnimation(FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer) {
}

bool AEndStaticMeshActor::IsActiveEmissiveColorAnimation() const {
    return false;
}


