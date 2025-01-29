#include "EndCharacterBase.h"
#include "EndCharacterMovementComponent.h"
#include "EndCharacterRootComponent.h"
#include "EndSkeletalMeshComponent.h"

AEndCharacterBase::AEndCharacterBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndCharacterRootComponent>(TEXT("CollisionCylinder")).SetDefaultSubobjectClass<UEndSkeletalMeshComponent>(TEXT("CharacterMesh0")).SetDefaultSubobjectClass<UEndCharacterMovementComponent>(TEXT("CharMoveComp"))) {
    this->bUseControllerRotationYaw = false;
    const FProperty* p_CapsuleComponent = GetClass()->FindPropertyByName("CapsuleComponent");
    (*p_CapsuleComponent->ContainerPtrToValuePtr<UCapsuleComponent*>(this)) = (UCapsuleComponent*)RootComponent;
    this->DitherFadeSettingFlag = 0;
    this->OverwriteNearFadeDistance = -1.00f;
    this->AdditionalNearFadeRadius = 0.00f;
    this->PlayerController = NULL;
    this->ActiveController = NULL;
    this->AIController = NULL;
    this->AITemplateData = NULL;
    this->StartSwimmingDepth = -1.00f;
    this->bForceUpdateKinematicBonesUpdateToPhysics = false;
    this->bAutoSetMeshRelativeLocation = true;
    this->BodyControlRig = NULL;
    this->FacialControlRig = NULL;
    this->EmissiveColorComponent = NULL;
    this->OverrideEmissiveColorSettings = NULL;
    this->LightAnimationComponent = NULL;
    this->CoordinateAnimationComponent = NULL;
    this->FlowMapAnimationComponent = NULL;
    this->bForceUpdateAnimation = false;
    this->bOverrideMovementExpressionSetting = false;
    this->bResidentEffectIgnoreWorldPause = false;
    this->bStopResidentEffectOnDead = true;
    this->bDontPlayResidentEffectAtStart = false;
    this->bIgnoreAutoSetCastShadow = false;
    this->VoiceEffectType = EEndVoiceEffectType::None;
    this->SoundSettingData = NULL;
    this->SoundDetectionSetting = NULL;
    this->AutoSeProcLodSetting = NULL;
    this->SoundIndexTable = NULL;
    this->bEnabledFootAttribute = true;
    this->bUpdateFootAttributeWithoutAutoSeSetting = false;
    this->AutoSeLODIntervalUnit = 1000.00f;
    this->MaterialPack = NULL;
    this->RandomSoundVoiceResource = NULL;
    const FProperty* p_Mesh = GetClass()->FindPropertyByName("Mesh");
    (*p_Mesh->ContainerPtrToValuePtr<USkeletalMeshComponent*>(this))->SetupAttachment(RootComponent);
}

void AEndCharacterBase::StopWeaponEmissiveColorAnimation(EWeaponSlot Slot, FName RequestID) {
}

void AEndCharacterBase::StopLightAnimation(FName RequestID) {
}

void AEndCharacterBase::StopFlowMapAnimation() {
}

void AEndCharacterBase::StopEmissiveColorAnimation(FName RequestID) {
}

void AEndCharacterBase::StopCoordinateAnimation(FName RequestID) {
}

void AEndCharacterBase::SetMaterialPack(UEndMaterialPack* InMaterialPack) {
}

void AEndCharacterBase::SetDirectEmissiveColor(FName RequestID, FName EmissiveColorSettingsId, float IntensityAlpha) {
}

void AEndCharacterBase::SetChildMesh(FName MeshName, FName Label) {
}

void AEndCharacterBase::ResetMaterialPack() {
}

void AEndCharacterBase::ResetDirectEmissiveColor(FName RequestID) {
}

void AEndCharacterBase::PlayWeaponEmissiveColorAnimation(EWeaponSlot Slot, FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer) {
}

void AEndCharacterBase::PlayLightAnimation(FName RequestID, FName LightAnimationSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset) {
}

void AEndCharacterBase::PlayFlowMapAnimation(float PlayRate, bool bOverrideConstantParameter, const FVector& ConstantParameter0, const FVector& ConstantParameter1) {
}

void AEndCharacterBase::PlayEmissiveColorAnimation(FName RequestID, FName EmissiveColorSettingsId, EEndAnimationModifierType ModifierType, EEndAnimationCurveType CurveType, UCurveFloat* CurveAsset, bool bCurveEvaluateInLogarithmicSpace, bool bLoop, float Duration, float RandomAdditiveDuration, float RandomOffset, float BlendInTime, float BlendOutTime, float StartOffset, float EndOffset, EEndAnimComponentControlLayer Layer) {
}

void AEndCharacterBase::PlayCoordinateAnimation(FName RequestID, FName CoordinateAnimationSettingsId, EEndAnimationCurveType CurveType, bool bLoop, float Duration) {
}

bool AEndCharacterBase::IsPlayer() const {
    return false;
}

bool AEndCharacterBase::IsActiveLightAnimation() const {
    return false;
}

bool AEndCharacterBase::IsActiveFlowMapAnimation() const {
    return false;
}

bool AEndCharacterBase::IsActiveEmissiveColorAnimation() const {
    return false;
}

bool AEndCharacterBase::IsActiveCoordinateAnimation() const {
    return false;
}

FRotator AEndCharacterBase::GetPointRotationFromOwnPosture(FVector InLocation) {
    return FRotator{};
}

FVector AEndCharacterBase::GetPointDirectionFromOwnPosture(FVector InLocation) {
    return FVector{};
}

FVector AEndCharacterBase::GetFeetLocation() const {
    return FVector{};
}


