#include "SQEX_Bonamik_Component.h"

USQEX_Bonamik_Component::USQEX_Bonamik_Component(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->fDeltaTime = 0.00f;
    this->m_BonamikAsset = NULL;
    this->CharacterMovementComponent = NULL;
    this->bEnableGameWind = false;
    this->m_BonamikEnable = true;
    this->m_BonamikAutoDisable = false;
    this->bAccurateBoundsUpdate = false;
    this->bPerJointWindSample = false;
    this->bForceFrontXAxis = false;
    this->PreRollStepOnResume = 0;
    this->ConstraintDampingAdjustFactor = 0.00f;
    this->PrevScreenSize = 100000002004087734272.00f;
    this->mTeleportDistance = 0.00f;
}

void USQEX_Bonamik_Component::SQEX_Bonamik_TurnOn(const TArray<FName>& Groups, float BlendTime) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_TurnOff(bool preserveLatestResult, const TArray<FName>& Groups, float BlendTime) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetWorldWindScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetWeight(float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight, bool AutoDisable) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetTeleportDistance(float Distance, int32 TeleportPreRollStep, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetSpeedRate(float SpeedRate, float SpeedRateChangeTime, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetPreRoll(int32 Step, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetParkRateScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetOuterConeScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetMassScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetLocalForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetInnerConeScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetGroupWeight(const TArray<FName>& Groups, float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetGroupFrozenState(const TArray<FName>& Groups, bool IsFrozen) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetGravity(const FVector& Gravity) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetFrozenState(bool IsFrozen) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnsemble(FName NewEnsemble) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnableTimestepSmoother(bool V) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnableGroundCollisionAll(bool bNewEnable) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnableGroundCollision(const TArray<FName>& Groups, bool bNewEnable) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnableGameWind(bool Enable) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnableExternalColliders(const TArray<FName>& Groups, bool V) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetEnable(bool NewEnable) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetChainRootTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetChainRootRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetChainRootImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetChainRootCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetBodyLiftScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetBodyDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetAutoDisable(bool AutoDisable) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetAnimPos(int32 BoneIndex, bool bForceSet) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetActorTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetActorRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetActorImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetActorCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_SetAccurateGroundCollisionAll(bool V) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_RestoreDefaultParameters() {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_ResetGravity() {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_Reset(bool bResetPose, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_ReplaceAsset(USQEX_BonamikAsset* originalAsset, USQEX_BonamikAsset* NewAsset) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_RemoveReferenceDefault() {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_RemoveReferenceCommon(USQEX_Bonamik_Component* OtherComponent) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_RemoveReferenceAll() {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_RemoveReference(USQEX_Bonamik_Component* OtherComponent, FName ReferenceGroupName) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_ReinitializeSimulationPose() {
}

bool USQEX_Bonamik_Component::SQEX_Bonamik_IsSetup() {
    return false;
}

bool USQEX_Bonamik_Component::SQEX_Bonamik_IsEnable() {
    return false;
}

bool USQEX_Bonamik_Component::SQEX_Bonamik_IsAutoDisable() {
    return false;
}

float USQEX_Bonamik_Component::SQEX_Bonamik_GetWeight() {
    return 0.0f;
}

float USQEX_Bonamik_Component::SQEX_Bonamik_GetTeleportDistance() {
    return 0.0f;
}

float USQEX_Bonamik_Component::SQEX_Bonamik_GetSpeedRate() const {
    return 0.0f;
}

int32 USQEX_Bonamik_Component::SQEX_Bonamik_GetNumReferences() const {
    return 0;
}

int32 USQEX_Bonamik_Component::SQEX_Bonamik_GetNumGroups() const {
    return 0;
}

FName USQEX_Bonamik_Component::SQEX_Bonamik_GetGroupName(int32 idx) const {
    return NAME_None;
}

FVector USQEX_Bonamik_Component::SQEX_Bonamik_GetGravity() const {
    return FVector{};
}

FName USQEX_Bonamik_Component::SQEX_Bonamik_GetEnsemble() const {
    return NAME_None;
}

void USQEX_Bonamik_Component::SQEX_Bonamik_Freeze(bool FreezeState, const TArray<FName>& Groups, float BlendTime, float BlendWeight) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_AddReferenceDefault() {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_AddReferenceCommon(USQEX_Bonamik_Component* OtherComponent) {
}

void USQEX_Bonamik_Component::SQEX_Bonamik_AddReference(USQEX_Bonamik_Component* OtherComponent, FName ReferenceGroupName) {
}


