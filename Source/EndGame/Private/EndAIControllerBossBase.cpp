#include "EndAIControllerBossBase.h"
#include "Templates/SubclassOf.h"

AEndAIControllerBossBase::AEndAIControllerBossBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bNotUseFieldDefinition = true;
    this->m_bPhaseChangeShareBase = false;
    this->m_bPhaseChangeAnyOneReaction = false;
    this->bUseOverrideAbilityTimeRate = false;
    this->OverrideAbilityTimeRate = 0.00f;
    this->bUseOverrideDamageTimeRate = false;
    this->OverrideDamageTimeRate = 1.00f;
    this->bUseOverrideActionRestrictionTimeRate = false;
    this->OverrideActionRestrictionTimeRate = 0.00f;
}

void AEndAIControllerBossBase::SwitchWallMove_EN0007() {
}

void AEndAIControllerBossBase::StopEnvironmentFeelerTornade(FName LevelName, FName AccessID, bool bDetach, bool bUseFade, float BlendTime) {
}

void AEndAIControllerBossBase::StopEnvironmentFeelerLaser(FName LevelName, FName AccessID, bool bDetach, bool bUseFade, float BlendTime) {
}

void AEndAIControllerBossBase::StopEnvironmentFeeler(FName LevelName, FName AccessID, bool bUseFade, float BlendTime) {
}

void AEndAIControllerBossBase::SetDebugChangePhase(int32 Phase) {
}

void AEndAIControllerBossBase::RestoreStalactite_EB2000() {
}

bool AEndAIControllerBossBase::RequestPhaseChangeAbility(FName AbilityId) {
    return false;
}

void AEndAIControllerBossBase::RequestManualPhaseChange(float Delay, bool CanPhaseChangeToDisableReaction) {
}

void AEndAIControllerBossBase::RemoveWallMoveSettings_EN0007() {
}

void AEndAIControllerBossBase::PlayEnvironmentFeelerTornade(FName LevelName, FName AccessID, FName DamageSourceID, bool bUseFade, float BlendTime) {
}

void AEndAIControllerBossBase::PlayEnvironmentFeelerLaser(FName LevelName, FName AccessID, FName AttachName, bool bUseFade, float BlendTime) {
}

void AEndAIControllerBossBase::PlayEnvironmentFeeler(FName LevelName, FName AccessID, bool bUseFade, float BlendTime) {
}















void AEndAIControllerBossBase::NotifyAbilitySuccessToTargetSystem(AEndCharacter* Target, EEndBattleAbilityActionCategory ActionCategory) {
}

bool AEndAIControllerBossBase::IsChangingPhase() {
    return false;
}

int32 AEndAIControllerBossBase::GetTotalStalactiteNum_EB2000() {
    return 0;
}

void AEndAIControllerBossBase::ForceStopEnemyCombinationAbility() {
}

bool AEndAIControllerBossBase::ForceRequestAction(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass) {
    return false;
}

void AEndAIControllerBossBase::FallStalactite_EB2000() {
}

void AEndAIControllerBossBase::ChangeWallMoveType_EN0007(EEndAiMoveType MoveType) {
}


