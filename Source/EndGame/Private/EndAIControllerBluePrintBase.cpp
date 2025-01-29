#include "EndAIControllerBluePrintBase.h"
#include "Templates/SubclassOf.h"

AEndAIControllerBluePrintBase::AEndAIControllerBluePrintBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->FollowTeleportEQS = NULL;
    this->FollowTeleportEQS_BuggyGetOff = NULL;
    this->FollowTeleportEQS_SequencerPv = NULL;
    this->FollowTeleportEQS_FastTravel = NULL;
    this->FollowMoveRateDash = 1.00f;
    this->FollowMoveRateRun = 1.00f;
    this->FollowMoveRateJog = 1.00f;
    this->FollowMoveRateWalk = 1.00f;
}

bool AEndAIControllerBluePrintBase::ToggleDebugEditMode() {
    return false;
}

void AEndAIControllerBluePrintBase::TestUniqueStalker() {
}

void AEndAIControllerBluePrintBase::TestMoveTo_AIState(FVector InVector) {
}

void AEndAIControllerBluePrintBase::TestFollowStalker() {
}

void AEndAIControllerBluePrintBase::TestFollowForceMainFollow() {
}

void AEndAIControllerBluePrintBase::TestFollowFastTravel() {
}

void AEndAIControllerBluePrintBase::TestFollowDate() {
}

void AEndAIControllerBluePrintBase::TestFollowChocoboFree() {
}

void AEndAIControllerBluePrintBase::StartFollowBackwardLeaveLeaderToPoint_Test() {
}

void AEndAIControllerBluePrintBase::SetVisibilityWeapon(bool bVisible, EWeaponSlot weaponSlotType) {
}

void AEndAIControllerBluePrintBase::SetSpecialStatusStateChangeID(EEndBattleSpecialStatusChangeType Type, FName stateChangeID, FName paramID) {
}

void AEndAIControllerBluePrintBase::SetPushCollisionEnable(FName partId, bool Enable) {
}

void AEndAIControllerBluePrintBase::SetOverrideUpperAnim(const FName InName, const FName InInterIn, const FName InInterOut) {
}

void AEndAIControllerBluePrintBase::SetOverrideKeepFromAbility(FName InAbilityName) {
}

void AEndAIControllerBluePrintBase::SetOverrideKeep(int32 InKeep) {
}

void AEndAIControllerBluePrintBase::SetOverrideActiveAimAngle(FVector2D ActiveYawRange, FVector2D ActivePitchRange) {
}

void AEndAIControllerBluePrintBase::SetOverrideAbilityKeep(int32 Value) {
}

void AEndAIControllerBluePrintBase::SetMeshDisp(bool InDisp) {
}

void AEndAIControllerBluePrintBase::SetHPPercent(int32 Percent) {
}

void AEndAIControllerBluePrintBase::SetForceDefaultCollisionSetting() {
}

void AEndAIControllerBluePrintBase::SetEnabledUpdateAimLocation(bool bEnabled) {
}

void AEndAIControllerBluePrintBase::SetDisableSuspendAction(bool Disable) {
}

void AEndAIControllerBluePrintBase::SetDisableResidualParticlesAbility(bool Disable) {
}

void AEndAIControllerBluePrintBase::SetDisableReaction(bool Disable) {
}

void AEndAIControllerBluePrintBase::SetCharacterRotation(FRotator InRotation) {
}

void AEndAIControllerBluePrintBase::SetCharacterLocation(FVector InLocation, bool bTeleportPhysics) {
}

void AEndAIControllerBluePrintBase::SetCapturableBySummon(bool Flag) {
}

void AEndAIControllerBluePrintBase::SetBattleSafeTransform(bool bEnable) {
}

void AEndAIControllerBluePrintBase::SendBPMessageToBattleScene(AEndCharacter* SendCharacter, const FName& Message) {
}

void AEndAIControllerBluePrintBase::ResetTrans() {
}

void AEndAIControllerBluePrintBase::ResetOverrideUpperAnim(bool InPlayEndAnim) {
}

void AEndAIControllerBluePrintBase::ResetOverrideKeep() {
}

void AEndAIControllerBluePrintBase::ResetOverrideActiveAimAngle() {
}

bool AEndAIControllerBluePrintBase::RequestTrans(TSubclassOf<UEndAITransDefinition> TransDefinitionClass) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestTakeDamageCounterCombo(TSubclassOf<UEndAIComboDefinitionReactionCounter> ComboCounterDefinitionClass, AEndCharacter* CauserChara, FName AbilityId, EEndBattleAbilityCommandType CommandType, FName DamageSourceID) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestTakeDamageCounterAndMove(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, FName AbilityId, EEndBattleAbilityCommandType CommandType, FName DamageSourceID) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestTakeDamageCounter(TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, FName AbilityId, EEndBattleAbilityCommandType CommandType, FName DamageSourceID) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestReactionGuard(TSubclassOf<UEndAIGuardDefinitionReaction> GuardDefinitionClass, AEndCharacter* CauserChara, int32 HandleId) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestReactionCounterCombo(TSubclassOf<UEndAIComboDefinitionReactionCounter> ComboCounterDefinitionClass, AEndCharacter* CauserChara, int32 HandleId) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestReactionCounterAndMove(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, int32 HandleId) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestReactionCounter(TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, int32 HandleId) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestReactionAvoid(TSubclassOf<UEndAIAvoidDefinitionReaction> AvoidDefinitionClass, AEndCharacter* CauserChara, int32 HandleId) {
    return false;
}

void AEndAIControllerBluePrintBase::RequestPlayBattleCameraSequence(FName CameraSequenceID, AEndCharacterBase* OwnerChara, AEndCharacterBase* HasResourceChara, AActor* TargetActor, bool bIsToRegisterSlaveViewOnly, float MassiveEnvironmentFrustrumScaleForMainPass) {
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestGuardHitCounterPackArrayLot(FName DefenseID, bool bExecuteTiming, TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList, TArray<int32> LotProbabilities) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestGuardHitCounterPackArray(FName DefenseID, bool bExecuteTiming, TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestGuardHitCounterPack(FName DefenseID, bool bExecuteTiming, TSubclassOf<UEndAIActionPackBase> ActionPackClass) {
    return FEndAIActionPackReturnInfo{};
}

bool AEndAIControllerBluePrintBase::RequestGuardHitCounter(FName DefenseID, bool bExecuteTiming, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestCombinationSpecial(TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass, bool bLast) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestCancelReactionAvoidToAction(TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass) {
    return false;
}

void AEndAIControllerBluePrintBase::RequestAttachSyncAction() {
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestActionPackArrayLot(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList, TArray<int32> LotProbabilities) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestActionPackArray(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestActionPack(TSubclassOf<UEndAIActionPackBase> ActionPackClass) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestActionInterruptPackArrayLot(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList, TArray<int32> LotProbabilities) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestActionInterruptPackArray(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList) {
    return FEndAIActionPackReturnInfo{};
}

FEndAIActionPackReturnInfo AEndAIControllerBluePrintBase::RequestActionInterruptPack(TSubclassOf<UEndAIActionPackBase> ActionPackClass) {
    return FEndAIActionPackReturnInfo{};
}

bool AEndAIControllerBluePrintBase::RequestActionInterrupt(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestActionChild(TSubclassOf<UEndAIActionDefinitionBase> InActionDefinitionClass, FName ChildActionId) {
    return false;
}

bool AEndAIControllerBluePrintBase::RequestAction(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass) {
    return false;
}

void AEndAIControllerBluePrintBase::RemoveSpecialStatusByID(FName ID) {
}

void AEndAIControllerBluePrintBase::RemoveSpecialStateEffect(FName specialStateEffectID) {
}

void AEndAIControllerBluePrintBase::RemoveAttachEffect(const FName AttachSocketName, const FName ResourceName, bool bDestroy) {
}

int32 AEndAIControllerBluePrintBase::PlayBattleCameraSequence(FName SequenceID) {
    return 0;
}
















void AEndAIControllerBluePrintBase::OnStartSequencerPV_Test2() {
}

void AEndAIControllerBluePrintBase::OnStartSequencerPV_Test() {
}




















void AEndAIControllerBluePrintBase::OnHitDamageSource_Implementation(bool& outDestroySrcDamageSoruce, const FName& SrcDamageSourceID, const FName& HitDamageSourceID) {
}


bool AEndAIControllerBluePrintBase::OnGetTargetFieldPosition_Implementation(FVector& OutPosition, FName InBattleAbilityID, FName InDamageSourceID, FName InAnimationName) {
    return false;
}

AActor* AEndAIControllerBluePrintBase::OnGetTargetFieldActor_Implementation(FName InBattleAbilityID) {
    return NULL;
}

bool AEndAIControllerBluePrintBase::OnGetCreateFieldPosition_Implementation(FVector& OutPosition, FQuat& outQuat, FName InBattleAbilityID, FName InDamageSourceID, FName InAnimationName) {
    return false;
}

bool AEndAIControllerBluePrintBase::OnGetAbilityJumpLandLocationAndRotation_Implementation(FVector& OutLocation, FRotator& OutRotation, FName InBattleAbilityID) {
    return false;
}

bool AEndAIControllerBluePrintBase::OnGetAbilityJumpLandLocation_Implementation(FVector& OutLocation, FName InBattleAbilityID) {
    return false;
}




void AEndAIControllerBluePrintBase::OnEndSequencerPV_Test() {
}













void AEndAIControllerBluePrintBase::OnCutChangeSequencerPV_Test(bool bEndShot) {
}






void AEndAIControllerBluePrintBase::OnCameraBlendOutSequencerPV_Test() {
}









void AEndAIControllerBluePrintBase::NotifyAbilityReaction(float Param0) {
}

bool AEndAIControllerBluePrintBase::IsRangeArea2D(AEndCharacter* InChara, FVector InLocation, float InRadius) {
    return false;
}

bool AEndAIControllerBluePrintBase::IsOverrideUpperAnim() {
    return false;
}

bool AEndAIControllerBluePrintBase::IsInSyncAction() const {
    return false;
}

void AEndAIControllerBluePrintBase::IsInRangeToTargetBranch(float InMin, float InMax, EEndAiMathBinCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal, bool bIgnoreCharacterRadius) {
}

bool AEndAIControllerBluePrintBase::IsInRangeToTarget(float InMin, float InMax, bool bIgnoreCharacterRadius) {
    return false;
}

bool AEndAIControllerBluePrintBase::IsInDummyBattle() const {
    return false;
}

void AEndAIControllerBluePrintBase::IsInAngleToTargetBranch(float InAngle, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal, bool InReverse) {
}

bool AEndAIControllerBluePrintBase::IsInAngleToTarget(float InAngle, bool InReverse) {
    return false;
}

bool AEndAIControllerBluePrintBase::IsIdle() {
    return false;
}

bool AEndAIControllerBluePrintBase::IsHPPercent(int32 Percent, EEndAiMathCmp Cmp) {
    return false;
}

bool AEndAIControllerBluePrintBase::IsForceTeleportingFollowAIPartyMemberAll() {
    return false;
}

bool AEndAIControllerBluePrintBase::IsExistSpawnWeaponCharacter(EEndBattleUniqueAbilitySpawnWeaponType spawnWeaponType, FName uniqueWeaponName) {
    return false;
}

bool AEndAIControllerBluePrintBase::IsEditor() const {
    return false;
}

bool AEndAIControllerBluePrintBase::IsDelayProcessing() {
    return false;
}

bool AEndAIControllerBluePrintBase::IsDebugEditMode() const {
    return false;
}

bool AEndAIControllerBluePrintBase::IsActionRestriction() {
    return false;
}

bool AEndAIControllerBluePrintBase::HasSpecialStatusByID(FName ID) {
    return false;
}

bool AEndAIControllerBluePrintBase::HasSpecialStatus(EEndBattleSpecialStatusChangeType Type) {
    return false;
}

bool AEndAIControllerBluePrintBase::HasDamageSource(FName DamageSourceID) {
    return false;
}

FVector AEndAIControllerBluePrintBase::GetVectorToTarget() {
    return FVector{};
}

bool AEndAIControllerBluePrintBase::GetTargetJumpBurstInput_Implementation(FEndBattleTargetJumpBurstInput& Input) {
    return false;
}

AEndCharacter* AEndAIControllerBluePrintBase::GetTarget() const {
    return NULL;
}

TArray<AEndCharacter*> AEndAIControllerBluePrintBase::GetSyncActionCharacter(TEnumAsByte<EEndAiBattleTargetType::Type> InTarget) {
    return TArray<AEndCharacter*>();
}

void AEndAIControllerBluePrintBase::GetSpecialStatusType(TArray<EEndBattleSpecialStatusChangeType>& typeList) const {
}

float AEndAIControllerBluePrintBase::GetSpecialStatusParamFloat(EEndBattleSpecialStatusChangeType Type, FName paramID) const {
    return 0.0f;
}

TArray<AEndCharacter*> AEndAIControllerBluePrintBase::GetSpecialStatusChangeCharacter(TEnumAsByte<EEndAiBattleTargetType::Type> InTarget, EEndBattleSpecialStatusChangeType Type) {
    return TArray<AEndCharacter*>();
}

AEndCharacter* AEndAIControllerBluePrintBase::GetSpawnWeaponCharacter(EEndBattleUniqueAbilitySpawnWeaponType weaponType, FName uniqueWeaponName) {
    return NULL;
}

AEndCharacter* AEndAIControllerBluePrintBase::GetPlayerLeader() {
    return NULL;
}

float AEndAIControllerBluePrintBase::GetPathDistanceFromTarget(FVector Location) {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetPathDistance(FVector Location) {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetNearestOpponentDistance(bool bIgnoreCharacterRadius) {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetLocationAngleAbs(FVector Loc, AEndCharacter* Target) const {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetLocationAngle(FVector Loc, AEndCharacter* Target) const {
    return 0.0f;
}

AEndCharacter* AEndAIControllerBluePrintBase::GetLeader() {
    return NULL;
}

int32 AEndAIControllerBluePrintBase::GetHPPercent() {
    return 0;
}

int32 AEndAIControllerBluePrintBase::GetHPMax() {
    return 0;
}

float AEndAIControllerBluePrintBase::GetHeightDistanceToTarget(bool bAbs) {
    return 0.0f;
}

bool AEndAIControllerBluePrintBase::GetFirstDamageTime(float& FirstDamageTime, const UAnimSequence* AnimSequecne, float StartTime) const {
    return false;
}

float AEndAIControllerBluePrintBase::GetDistanceToTarget2D(bool bIgnoreCharacterRadius) {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetDistanceToTarget(bool bIgnoreCharacterRadius) {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetDistanceToCharacter2D(AEndCharacter* InCharacter, bool bIgnoreCharacterRadius) {
    return 0.0f;
}

float AEndAIControllerBluePrintBase::GetDistanceToCharacter(AEndCharacter* InCharacter, bool bIgnoreCharacterRadius) {
    return 0.0f;
}

FName AEndAIControllerBluePrintBase::GetCharaSpecName() {
    return NAME_None;
}

FRotator AEndAIControllerBluePrintBase::GetCharacterRotation() const {
    return FRotator{};
}

FVector AEndAIControllerBluePrintBase::GetCharacterLocation() const {
    return FVector{};
}

FVector AEndAIControllerBluePrintBase::GetCharacterFeetLocation() const {
    return FVector{};
}

AEndCharacter* AEndAIControllerBluePrintBase::GetCharacter() {
    return NULL;
}

float AEndAIControllerBluePrintBase::GetAngleToTarget(bool bAbs) {
    return 0.0f;
}

bool AEndAIControllerBluePrintBase::GetAbilityLoopMoveStartSpecifiedTargetLocation_Implementation(FVector& OutLocation, FName AbilityId) {
    return false;
}

bool AEndAIControllerBluePrintBase::GetAbilityLoopMoveNextSpecifiedTargetLocation_Implementation(FVector& OutLocation, FName AbilityId) {
    return false;
}


bool AEndAIControllerBluePrintBase::ForceTeleportFollowAIPartyMemberAll() {
    return false;
}

void AEndAIControllerBluePrintBase::ForceDisableAimEffectorSetting(FName EffectorSettingName) {
}

void AEndAIControllerBluePrintBase::EndFollowBackwardLeaveLeaderToPoint_Test() {
}

void AEndAIControllerBluePrintBase::EnableDamageReactionOwnerSyncAction() {
}

void AEndAIControllerBluePrintBase::DoOnceWithThen(const EEndDoOnceCode Code, FLatentActionInfo LatentInfo, EEndDoOnceOutCode& Result) {
}

void AEndAIControllerBluePrintBase::DestroyDamageSource(FName DamageSourceID, bool bDestroyEffect) {
}

void AEndAIControllerBluePrintBase::DebugLocalLog(const FString& inString, FLinearColor TextColor) {
}

void AEndAIControllerBluePrintBase::DebugEditModeBranch(EEndAIExecPinBranch& PinBranch) {
}

void AEndAIControllerBluePrintBase::DeactivatePBDConstraint(float BlendTime) {
}

void AEndAIControllerBluePrintBase::CreateSyncAction(FName SyncActionID, AEndCharacter* targetChara, bool bOverwrite) {
}

void AEndAIControllerBluePrintBase::CreateDamageSource(FName DamageSourceID, AEndCharacter* targetChara, FName AbilityId, bool bOverrideDamage, int32 OverrideDamage) {
}

void AEndAIControllerBluePrintBase::CheckDistanceToTargetBranch(float InDistance, EEndAiMathCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal, bool bIgnoreCharacterRadius) {
}

bool AEndAIControllerBluePrintBase::CheckDistanceToTarget(float InDistance, EEndAiMathCmp Cmp, bool bIgnoreCharacterRadius) {
    return false;
}

bool AEndAIControllerBluePrintBase::CanSeeTarget(bool bValidBlock) {
    return false;
}

void AEndAIControllerBluePrintBase::CancelActionChild(FName ChildActionId) {
}

void AEndAIControllerBluePrintBase::AIDelay(UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo) {
}

void AEndAIControllerBluePrintBase::AddSpecialStatusByID(FName ID) {
}

void AEndAIControllerBluePrintBase::AddSpecialStateEffectWithBeamTarget(FName specialStateEffectID, TArray<AEndCharacter*> beamTargetCharaList) {
}

void AEndAIControllerBluePrintBase::AddSpecialStateEffect(FName specialStateEffectID) {
}

void AEndAIControllerBluePrintBase::AddAttachEffect(FEndCharacterAttachEffectArguments args) {
}

void AEndAIControllerBluePrintBase::ActivatePBDConstraint(float BlendTime) {
}


