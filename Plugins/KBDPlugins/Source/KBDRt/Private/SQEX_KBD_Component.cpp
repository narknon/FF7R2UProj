#include "SQEX_KBD_Component.h"

USQEX_KBD_Component::USQEX_KBD_Component(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CharacterMovementComponent = NULL;
}

void USQEX_KBD_Component::SQEX_KineDriver_SetParam(TMap<FName, float> Params) {
}

void USQEX_KBD_Component::SQEX_KineDriver_SetEnableBone(bool NewEnable, FName BoneName, float PauseRate, bool bApplyBonamik, bool bApplyChildren) {
}

void USQEX_KBD_Component::SQEX_KineDriver_SetEnable(bool NewEnable, FName NewLabel) {
}

bool USQEX_KBD_Component::SQEX_KineDriver_IsEnable() const {
    return false;
}

void USQEX_KBD_Component::SQEX_Bonamik_TurnOn(const TArray<FName>& Groups, float BlendTime) {
}

void USQEX_KBD_Component::SQEX_Bonamik_TurnOff(bool preserveLatestResult, const TArray<FName>& Groups, float BlendTime) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetWorldWindScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetWeight(float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight, bool AutoDisable) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetSpeedRate(float SpeedRate, float SpeedRateChangeTime, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetPreRoll(int32 Step, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetParkRateScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetOuterConeScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetMassScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetLocalForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetInnerConeScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetGroupWeight(const TArray<FName>& Groups, float Weight, float WeightChangeTime, bool ResetWhenNonZeroWeight) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetGroupFrozenState(const TArray<FName>& Groups, bool IsFrozen) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetGravity(const FVector& Gravity) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetFrozenState(bool IsFrozen) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetEnsemble(FName NewEnsemble) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetEnableGroundCollisionAll(bool bNewEnable) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetEnableGroundCollision(const TArray<FName>& Groups, bool bNewEnable) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetEnableExternalColliders(const TArray<FName>& Groups, bool V) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetEnable(bool NewEnable) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetChainRootTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetChainRootRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetChainRootImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetChainRootFictitiousForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetChainRootCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyVelocityDampingScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyRadiusScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyLiftScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyGravityScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyFrictionScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyDampingScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetBodyConstraintDampingScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetAutoDisable(bool AutoDisable) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetActorTransDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetActorRotDragScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetActorImpulseScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetActorFictitiousForceScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetActorCentrifugalScale(const TArray<FName>& Groups, float Scale, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_SetAccurateGroundCollisionAll(bool V) {
}

void USQEX_KBD_Component::SQEX_Bonamik_RestoreDefaultParameters() {
}

void USQEX_KBD_Component::SQEX_Bonamik_ResetGravity() {
}

void USQEX_KBD_Component::SQEX_Bonamik_Reset(bool bResetPose, TEnumAsByte<ESQEX_Bonamik_PropagationMode> PropagationMode) {
}

void USQEX_KBD_Component::SQEX_Bonamik_RemoveWorldWindModifier(USceneComponent* Component, UObject* Outer) {
}

void USQEX_KBD_Component::SQEX_Bonamik_RemoveWind(USceneComponent* Component, UObject* Outer) {
}

void USQEX_KBD_Component::SQEX_Bonamik_ReinitializeSimulationPose() {
}

bool USQEX_KBD_Component::SQEX_Bonamik_IsEnable() const {
    return false;
}

bool USQEX_KBD_Component::SQEX_Bonamik_IsAutoDisable() const {
    return false;
}

float USQEX_KBD_Component::SQEX_Bonamik_GetSpeedRate() const {
    return 0.0f;
}

int32 USQEX_KBD_Component::SQEX_Bonamik_GetNumGroups() const {
    return 0;
}

FName USQEX_KBD_Component::SQEX_Bonamik_GetGroupName(int32 idx) const {
    return NAME_None;
}

FVector USQEX_KBD_Component::SQEX_Bonamik_GetGravity() const {
    return FVector{};
}

FName USQEX_KBD_Component::SQEX_Bonamik_GetEnsemble() const {
    return NAME_None;
}

void USQEX_KBD_Component::SQEX_Bonamik_Freeze(bool FreezeState, const TArray<FName>& Groups) {
}

void USQEX_KBD_Component::SQEX_Bonamik_FixedFrameRateThisFrame() {
}

void USQEX_KBD_Component::SQEX_Bonamik_AddOrSetWorldWindModifier(USceneComponent* Component, USQEX_BonamikWind_Asset* Wind, float Scale, UObject* Outer) {
}

void USQEX_KBD_Component::SQEX_Bonamik_AddOrSetWorldWind(USceneComponent* Component, const TArray<FSQEX_BonamikWind_Desc>& Winds, const FTransform& Offset, float Scale, UObject* Outer) {
}

void USQEX_KBD_Component::SQEX_Bonamik_AddOrSetWindDirect(USceneComponent* Component, const FSQEX_BonamikWind_Desc& Wind, const FTransform& Offset, float Scale, bool bDisableWorldWind, UObject* Outer) {
}

void USQEX_KBD_Component::SQEX_Bonamik_AddOrSetWind(USceneComponent* Component, USQEX_BonamikWind_Asset* Wind, const FTransform& Offset, float Scale, bool bDisableWorldWind, UObject* Outer) {
}


