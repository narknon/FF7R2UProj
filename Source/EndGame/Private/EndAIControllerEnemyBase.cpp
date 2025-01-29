#include "EndAIControllerEnemyBase.h"
#include "Templates/SubclassOf.h"

AEndAIControllerEnemyBase::AEndAIControllerEnemyBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->LightAttackInterval = 3.00f;
    this->LightAttackIntervalWidth = 0.00f;
    this->HardAttackInterval = 15.00f;
    this->HardAttackIntervalWidth = 0.00f;
    this->bDisableReturnToBattleArea = false;
    this->m_ReturnHomeMoveDefinitionClass = NULL;
    this->bNotUseFieldDefinition = false;
    this->DefaultReturnFieldDefinitionClass = NULL;
    this->bUseFieldEQSTerritoryFilter = true;
    this->bActiveAITimerToDebugMode = false;
    this->bDisableBattleAreaErrorLog = false;
}

int32 AEndAIControllerEnemyBase::ToRestoreParts(FName keyword) {
    return 0;
}

void AEndAIControllerEnemyBase::ToRepairWithHPPercent(FName charaPartsSpecName, FName meshLabelName, float HPPercent) {
}

int32 AEndAIControllerEnemyBase::ToDestructionParts(FName keyword) {
    return 0;
}

bool AEndAIControllerEnemyBase::ToChangeParts(FName MeshName, FName MeshLabel) {
    return false;
}

void AEndAIControllerEnemyBase::ToBreak(FName charaPartsSpecName) {
}

void AEndAIControllerEnemyBase::TemporaryWithdrawalGroup(FName InGroupId) {
}

void AEndAIControllerEnemyBase::StopExtraIntervalAll() {
}

void AEndAIControllerEnemyBase::StopExtraInterval(FName ID) {
}

void AEndAIControllerEnemyBase::StopAITimer(FName ID) {
}

void AEndAIControllerEnemyBase::StartExtraInterval(FName ID) {
}

bool AEndAIControllerEnemyBase::StartBurst(bool Force) {
    return false;
}

void AEndAIControllerEnemyBase::StartAITimer(FName ID, float Time) {
}

void AEndAIControllerEnemyBase::SetTopPriorityActionConditionResult(FName TopPriorityActionId, int32 Priority, bool bResult) {
}

void AEndAIControllerEnemyBase::SetReserveWarpDefinitionTargetPointNames(TArray<FName> TargetPointNames) {
}

void AEndAIControllerEnemyBase::SetReserveWarpDefinitionTargetLocations(TArray<FVector> Locations) {
}

void AEndAIControllerEnemyBase::SetReserveMoveToMultiPointDefinitionTargetLocations(TArray<FVector> Locations) {
}

void AEndAIControllerEnemyBase::SetOverrideBattleCharaSpec(FName BattleCharaSpecID) {
}

void AEndAIControllerEnemyBase::SetOverrideBattleCharaPartsSpec(FName BaseID, FName OverrideId, bool bChangeHP) {
}

void AEndAIControllerEnemyBase::SetNextWarpPosition(const FVector& WarpPosition) {
}

void AEndAIControllerEnemyBase::SetLockTargetBP(AEndCharacter* Target, bool bImmediate) {
}

void AEndAIControllerEnemyBase::SetIgnoreRightToAttack(bool bIgnore) {
}

void AEndAIControllerEnemyBase::SetHPMinLimitPercent(int32 InPercent) {
}

void AEndAIControllerEnemyBase::SetExtraConditionResult(FName ConditionTag, bool bResult) {
}

void AEndAIControllerEnemyBase::SetDisableTargetPoint(FName SocketName, bool bDisable) {
}

void AEndAIControllerEnemyBase::SetDisableBurst(bool Disable) {
}

void AEndAIControllerEnemyBase::SetDisableBPDamage(bool Disable) {
}

void AEndAIControllerEnemyBase::SetDefinitionLockTargetResult(FName LockTargetTag, AEndCharacter* Target) {
}

void AEndAIControllerEnemyBase::SetBurstForceAerial(bool Flag) {
}

void AEndAIControllerEnemyBase::SetBPPercent(float Value) {
}

void AEndAIControllerEnemyBase::SetBPDamageCoefficient(float Coefficient) {
}

void AEndAIControllerEnemyBase::SetBPAttackChance(bool Enable) {
}

void AEndAIControllerEnemyBase::SetBP(float Value) {
}

void AEndAIControllerEnemyBase::SetBodyDummyParts(FName PartsID) {
}

void AEndAIControllerEnemyBase::SetBGFAStatus(FName AccessorID, FName StateId) {
}

void AEndAIControllerEnemyBase::SetAngleRangeTargetPoint(FName SocketName, float baseAngle, float angleRange) {
}

void AEndAIControllerEnemyBase::SetAIActionStatusRecastTime(TArray<TSubclassOf<UEndAIActionDefinition>> ActionDefClassList, float RecastTime) {
}

void AEndAIControllerEnemyBase::SendGroupMessage(FName Message, EEndAIBattleGroupNotify NotifyType, FName GroupId, FName IndividualTag) {
}

void AEndAIControllerEnemyBase::SelfDisappear(bool drawPause) {
}

void AEndAIControllerEnemyBase::RewriteExtraInterval(FName ID, float Interval, float IntervalWidth) {
}

void AEndAIControllerEnemyBase::RewriteAttackInterval(EEndAIIntervalType IntervalType, float Interval, float IntervalWidth) {
}

void AEndAIControllerEnemyBase::ReturnGroup(FName InGroupId) {
}

void AEndAIControllerEnemyBase::RestartExtraIntervalAll() {
}

void AEndAIControllerEnemyBase::RestartExtraInterval(FName ID) {
}

void AEndAIControllerEnemyBase::RestartAttackIntervalAll() {
}

void AEndAIControllerEnemyBase::RestartAttackInterval(EEndAIIntervalType IntervalType) {
}

bool AEndAIControllerEnemyBase::RestartAITimer(FName ID) {
    return false;
}

void AEndAIControllerEnemyBase::ResetOverrideBattleCharaSpec() {
}

void AEndAIControllerEnemyBase::ResetOverrideBattleCharaPartsSpec(FName BaseID) {
}

void AEndAIControllerEnemyBase::ResetLockTargetBP() {
}

void AEndAIControllerEnemyBase::ResetDefaultAttackInterval() {
}

void AEndAIControllerEnemyBase::ResetAttackIntervalElapsedTime(EEndAIIntervalType IntervalType) {
}

void AEndAIControllerEnemyBase::ResetAngleRangeTargetPoint(FName SocketName) {
}

void AEndAIControllerEnemyBase::ResetAIActionStatus(TArray<TSubclassOf<UEndAIActionDefinition>> ActionDefClassList, bool bTrialCount, bool TrialStraightCount, bool bRecastTime) {
}

bool AEndAIControllerEnemyBase::RequestStartCombinationTopPriority(TSubclassOf<UEndAIActionDefinitionBase> CombinationDefinitionClass, AEndCharacter* Target, FName TopPriorityActionId) {
    return false;
}

bool AEndAIControllerEnemyBase::RequestStartCombination(TSubclassOf<UEndAIActionDefinitionBase> CombinationDefinitionClass, AEndCharacter* Target) {
    return false;
}

void AEndAIControllerEnemyBase::RequestShowPreloadedWaveReinforcement(FName territoryID, FName reinforcementActorName, FTransform reinforcementStartPoint) {
}

bool AEndAIControllerEnemyBase::RequestNotificationComboAbilityInterrupt(TSubclassOf<UEndAIAbilityDefinition> AbilityDefinitionClass) {
    return false;
}

bool AEndAIControllerEnemyBase::RequestConnectActivatedAbilityCombo(TSubclassOf<UEndAIComboDefinition> ComboDefinitionClass, FName AbilityId) {
    return false;
}

bool AEndAIControllerEnemyBase::RequestCombinationCombo(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIComboDefinition> ComboDefinitionClass, bool bLast) {
    return false;
}

bool AEndAIControllerEnemyBase::RequestCombination(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIAbilityDefinition> AbilityDefinitionClass, bool bLast) {
    return false;
}

bool AEndAIControllerEnemyBase::RequestActionTopPriority(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass, FName TopPriorityActionId) {
    return false;
}

void AEndAIControllerEnemyBase::PauseExtraIntervalAll() {
}

void AEndAIControllerEnemyBase::PauseExtraInterval(FName ID) {
}

void AEndAIControllerEnemyBase::PauseAttackIntervalAll() {
}

void AEndAIControllerEnemyBase::PauseAttackInterval(EEndAIIntervalType IntervalType) {
}

bool AEndAIControllerEnemyBase::PauseAITimer(FName ID) {
    return false;
}





























void AEndAIControllerEnemyBase::NotifyAbilitySuccessToTargetSystem_EN2219(AEndCharacter* Target, EEndBattleAbilityActionCategory ActionCategory) {
}

bool AEndAIControllerEnemyBase::IsPlayingAICombination() {
    return false;
}

bool AEndAIControllerEnemyBase::IsInHateLock() {
    return false;
}

bool AEndAIControllerEnemyBase::IsInBattleArea() const {
    return false;
}

bool AEndAIControllerEnemyBase::IsGroupLeader(FName GroupId) {
    return false;
}

bool AEndAIControllerEnemyBase::IsDifficultyHard() {
    return false;
}

bool AEndAIControllerEnemyBase::IsDestruction(FName keyword) {
    return false;
}

bool AEndAIControllerEnemyBase::IsBurst() {
    return false;
}

bool AEndAIControllerEnemyBase::IsBPAttackChance() {
    return false;
}

bool AEndAIControllerEnemyBase::IsBGFAStatusBP(FName AccessorID, FName StateId) {
    return false;
}

bool AEndAIControllerEnemyBase::IsAIActionStatusRecastForId(FName AIActionStatusId) {
    return false;
}

bool AEndAIControllerEnemyBase::IsAIActionStatusRecast(TArray<TSubclassOf<UEndAIActionDefinition>> ActionDefClassList) {
    return false;
}

bool AEndAIControllerEnemyBase::IsAffiliatedGroup(AEndCharacter* Chara, FName GroupId) {
    return false;
}

bool AEndAIControllerEnemyBase::IsActiveAITimer(FName ID) const {
    return false;
}

FName AEndAIControllerEnemyBase::GetTransID() {
    return NAME_None;
}

int32 AEndAIControllerEnemyBase::GetPhase() const {
    return 0;
}

int32 AEndAIControllerEnemyBase::GetPartsHPPercent(FName PartsID) {
    return 0;
}

FName AEndAIControllerEnemyBase::GetOwnerTerritoryIdBP() const {
    return NAME_None;
}

FVector AEndAIControllerEnemyBase::GetNextWarpPosition() {
    return FVector{};
}

FName AEndAIControllerEnemyBase::GetMoveToMultiTargetName() {
    return NAME_None;
}

int32 AEndAIControllerEnemyBase::GetGroupMembersNum(FName GroupId, bool bIgnoreLeader) {
    return 0;
}

TArray<AEndCharacter*> AEndAIControllerEnemyBase::GetGroupMembers(FName GroupId, bool bIgnoreLeader) {
    return TArray<AEndCharacter*>();
}

AEndCharacter* AEndAIControllerEnemyBase::GetGroupIndividualMember(FName GroupId, FName IndividualTag) {
    return NULL;
}

void AEndAIControllerEnemyBase::GetExtraIntervalStatus(FName ID, float& ElapsedTime, bool& bActive, bool& bPause) const {
}

FEndAIDefinitionReturnTag AEndAIControllerEnemyBase::GetCurrentAIDefinitionTagToChara(AEndCharacter* InChara) const {
    return FEndAIDefinitionReturnTag{};
}

FEndAIDefinitionReturnTag AEndAIControllerEnemyBase::GetCurrentAIDefinitionTag() const {
    return FEndAIDefinitionReturnTag{};
}

void AEndAIControllerEnemyBase::GetComboCount(int32& Count, int32& NextCount) {
}

float AEndAIControllerEnemyBase::GetBPPercent() {
    return 0.0f;
}

float AEndAIControllerEnemyBase::GetBP() {
    return 0.0f;
}

float AEndAIControllerEnemyBase::GetAttackIntervalElapsedTime(EEndAIIntervalType IntervalType) const {
    return 0.0f;
}

float AEndAIControllerEnemyBase::GetAITimerRemainingTime(FName ID) {
    return 0.0f;
}

EActorMoveMode AEndAIControllerEnemyBase::GetAIMoveMode() {
    return EActorMoveMode::Ground;
}

EEndAIActionState AEndAIControllerEnemyBase::GetAIActionState() const {
    return EEndAIActionState::Standby;
}

void AEndAIControllerEnemyBase::ForceTakeDamegeHitReactionToParent(FName ReactionID) {
}

void AEndAIControllerEnemyBase::ForceEndCombination() {
}

void AEndAIControllerEnemyBase::EndGuardDefinition() {
}

void AEndAIControllerEnemyBase::EndBurstInstant() {
}

void AEndAIControllerEnemyBase::DisableLastHitAIPC(bool bDisable) {
}

void AEndAIControllerEnemyBase::ClearTopPriorityActionConditionAll() {
}

void AEndAIControllerEnemyBase::ClearTopPriorityActionCondition(FName TopPriorityActionId) {
}

void AEndAIControllerEnemyBase::ClearHPMinLimit() {
}

void AEndAIControllerEnemyBase::ClearBPDamageCoefficient() {
}

void AEndAIControllerEnemyBase::CheckAIActionStatus(TSubclassOf<UEndAIActionDefinition> ActionDefClass, bool& bResult, float& CoolTime, int32& TrialCount, int32& TrialStraightCount) {
}

void AEndAIControllerEnemyBase::ChangeCombinationTarget(AEndCharacter* InTarget) {
}


int32 AEndAIControllerEnemyBase::AddDestructionPartsName(FName keyword, FName MeshName, FName destructionPartsLabelName, FName restorePartsLabelName) {
    return 0;
}


