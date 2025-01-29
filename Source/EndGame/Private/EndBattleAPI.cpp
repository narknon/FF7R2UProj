#include "EndBattleAPI.h"

UEndBattleAPI::UEndBattleAPI() {
}

void UEndBattleAPI::ValidNearFadeEnvPhysicsActor() {
}

bool UEndBattleAPI::ValidateCombatAreaVolume(FName VolumeName, bool bValidate) {
    return false;
}

void UEndBattleAPI::UpdateMoveGenjiShield(AEndCharacter* ownerCharacter, AEndCharacter* causerCharacter) {
}

void UEndBattleAPI::UpdateAppearanceFrog(AEndCharacter* Character) {
}

bool UEndBattleAPI::TryLayoutTransform(FName NodeName) {
    return false;
}

bool UEndBattleAPI::TryGetCurrentFloorLocation(FVector& FloorLocation, AEndCharacterBase* Character) {
    return false;
}

bool UEndBattleAPI::SwitchMesh(AEndCharacter* Character, FName MeshName, FName MeshLabel) {
    return false;
}

void UEndBattleAPI::SummonTrigger() {
}

void UEndBattleAPI::SummonPointManualSuspend(bool suspend) {
}

void UEndBattleAPI::SummonFinishingBlow() {
}

void UEndBattleAPI::SummonCutSceneAbilityException(FName excludeCharaSpecID, FName substituteCharaSpecID) {
}

void UEndBattleAPI::StopPartStartLoopEndMotion(AEndCharacter* Character) {
}

void UEndBattleAPI::StopPartLoopMotion(AEndCharacter* Character) {
}

void UEndBattleAPI::StopEnvironmentPhysFieldForce(FName GroupName) {
}

void UEndBattleAPI::StopEffect(int32 handleNumber) {
}

void UEndBattleAPI::StopCrowdActor(FName LevelName, FName AccessID, float BlendTime, bool bUseFade) {
}

void UEndBattleAPI::StopBattleCameraSequence(int32 sequenceActorUID) {
}

void UEndBattleAPI::StopAnimEnvironment(FName LevelName, FName AccessID) {
}

void UEndBattleAPI::StopAddMotion(AEndCharacter* Character) {
}

void UEndBattleAPI::StartEnvironmentPhysFieldForce(FName GroupName) {
}

bool UEndBattleAPI::StartBurst(AEndCharacter* Character, bool Force) {
    return false;
}

bool UEndBattleAPI::SpawnWeaponCharacter(AEndCharacter* ownerCharacter, EEndBattleUniqueAbilitySpawnWeaponType weaponType, FName uniqueWeaponName, FName SpawnWeaponObjectName) {
    return false;
}

AActor* UEndBattleAPI::SpawnSharedCharaSpec(AEndCharacterBase* Character, int32 Index) {
    return NULL;
}

void UEndBattleAPI::SkipFadeCharaPopActor(FName ActorName) {
}

void UEndBattleAPI::ShowTargetAppearGUI(AEndCharacter* Character) {
}

void UEndBattleAPI::ShowPhysics(FName ActorName, bool bSimulatePhysics) {
}

void UEndBattleAPI::SetWalkableFloorAngleOnBattleNav(AEndCharacter* InCharacter, float InWalkableAngle) {
}

void UEndBattleAPI::SetWalkableFloorAngle(AEndCharacter* InCharacter, float InWalkableAngle) {
}

void UEndBattleAPI::SetVisibilityWeapon(AEndCharacter* Character, bool bVisible, EWeaponSlot weaponSlotType, bool bSetToAnimationDefault, bool bAlsoSetToNeutral) {
}

void UEndBattleAPI::SetValidSmallSizeForSummonArea(bool Valid) {
}

void UEndBattleAPI::SetValidLargeSizeForSummonArea(bool Valid) {
}

void UEndBattleAPI::SetupChargeCrystal(AEndCharacter* ownerCharacter, FName uniqueName) {
}

void UEndBattleAPI::SetUnitParameter(AEndCharacter* Character, bool hideTargetList, bool disableTarget, bool disableTargetShowIcon, bool DisableDamageHit) {
}

void UEndBattleAPI::SetSummonInBossCutScene(bool bFlag) {
}

void UEndBattleAPI::SetSubCollisionPushBackSpeed(AEndCharacter* InChara, float InSpeed) {
}

void UEndBattleAPI::SetStoryFlagCondition(FName storyFlagNames, bool Condition) {
}

void UEndBattleAPI::SetSpecialStatusStateChangeID(AEndCharacter* Character, EEndBattleSpecialStatusChangeType Type, FName stateChangeID, FName paramID) {
}

void UEndBattleAPI::SetSpecialStatusChangeStateChangeID(AEndCharacter* Character, FName SpecialStatusChangeID, FName stateChangeID, TArray<float> Params, FName paramID, AActor* paramActor) {
}

void UEndBattleAPI::SetShowEnemyStatusGUI(AEndCharacter* Character, bool Show) {
}

void UEndBattleAPI::SetRootCapsuleAttackTargetSizeScale(AEndCharacter* Character, FVector AttackTargetSizeScale) {
}

void UEndBattleAPI::SetRigidBodyName(AEndCharacter* Character, FName RigidBodyName, bool bDeactivateOther) {
}

void UEndBattleAPI::SetRewardDelayEndBattle() {
}

void UEndBattleAPI::SetPrimaryAnimPack(AEndCharacter* Character, const FName InName, bool ignoreLowerPriority) {
}

void UEndBattleAPI::SetPerchSweepRadiusScale(AEndCharacter* InChara, float InScale) {
}

bool UEndBattleAPI::SetPartyLeader(EPlayerType Player, bool bIsInputTrigered) {
    return false;
}

void UEndBattleAPI::SetPartsHPPercent(AEndCharacter* Character, FName BattleCharaPartsSpecID, float Percent) {
}

void UEndBattleAPI::SetOverridePartsCameraLockSocketName(AEndCharacter* Character, FName BaseBattleCharaPartsSpecID, FName SocketName, float BlendTime, EAlphaBlendOption BlendOption) {
}

void UEndBattleAPI::SetOverrideMovementBaseByComponentTags(AEndCharacter* InCharacter, AActor* InMovementBaseActor, FName ComponentTag) {
}

void UEndBattleAPI::SetOverrideLocomotionAnimSequenceName(AEndCharacter* InChara, EEndLocomotionAnimGroup AnimGroup, FName AnimSequenceName, float BlendTime) {
}

void UEndBattleAPI::SetOverrideKeepFromAbility(AEndCharacter* Character, FName InAbilityName) {
}

void UEndBattleAPI::SetOverrideKeep(AEndCharacter* Character, int32 InKeep) {
}

void UEndBattleAPI::SetOverrideEnemyBookID(AEndCharacter* Character, FName EnemyBookID) {
}

void UEndBattleAPI::SetOverrideCapsuleSize(AEndCharacter* InCharacter, float InRadius, float InCapsuleHalfHeight) {
}

void UEndBattleAPI::SetOverrideCameraLockSocketName(AEndCharacter* Character, FName SocketName, float BlendTime, EAlphaBlendOption BlendOption) {
}

void UEndBattleAPI::SetOverrideBattleDefenseID(AEndCharacter* Character, FName battleDefenseID) {
}

void UEndBattleAPI::SetOverrideBattleCharaSpec(AEndCharacter* Character, FName BattleCharaSpecID) {
}

void UEndBattleAPI::SetOverrideBattleCharaPartsSpec(AEndCharacter* Character, FName BaseID, FName OverrideId, bool bChangeHP) {
}

void UEndBattleAPI::SetOverrideAdditiveDamage(AEndCharacter* InChara, FName AnimSequenceName) {
}

void UEndBattleAPI::SetOverrideActiveAimAngle(AEndCharacter* Character, FVector2D ActiveYawRange, FVector2D ActivePitchRange) {
}

void UEndBattleAPI::SetOverrideAbilityKeep(AEndCharacter* Character, int32 Value) {
}

void UEndBattleAPI::SetMovementSplineConstraint(AEndCharacterBase* InCharacter, AActor* InSplineActor, FName ComponentTag) {
}

void UEndBattleAPI::SetLockHeat(AEndCharacter* Character, bool Locked) {
}

void UEndBattleAPI::SetInvalidPerchRadiusScale(AEndCharacter* InChara, float InScale) {
}

void UEndBattleAPI::SetImmotality(AEndCharacter* InChara, bool InImmotality) {
}

bool UEndBattleAPI::SetIgnoreSummonTargetPointFromActorName(FName InActorName, bool ignore) {
    return false;
}

void UEndBattleAPI::SetIgnorePushActorsByAccessID(AEndCharacter* Character, bool bIgnore, const TArray<FName>& AccessIDs) {
}

void UEndBattleAPI::SetIgnorePushActors(AEndCharacter* Character, bool bIgnore, const TArray<FName>& LevelNames, const TArray<FName>& ActorNames) {
}

void UEndBattleAPI::SetIgnoreMoveOnlyNavMesh(AEndCharacter* Character, bool bIgnoreMoveOnlyNavMesh) {
}

void UEndBattleAPI::SetIgnoreDisperseTarget(AEndCharacter* Character) {
}

void UEndBattleAPI::SetHPPercent(AEndCharacter* Character, int32 Percent) {
}

void UEndBattleAPI::SetHitCharaResponse(AEndCharacterBase* Character, bool bHitChara) {
}

void UEndBattleAPI::SetHideTargetList(AEndCharacter* Character, bool hide) {
}

void UEndBattleAPI::SetHideSummonWithSkillCamera(bool enableHide) {
}

void UEndBattleAPI::SetHide(AEndCharacter* Character, bool hide) {
}

void UEndBattleAPI::SetHiddenVolumeRelatedBreakable(EEndBattleBreakableRelationVolumeType VolumeType, bool bHidden, const TArray<FName>& BreakableIDs) {
}

void UEndBattleAPI::SetHiddenBreakablesTwoParam(bool bHidden, const TArray<FName>& AccessIDs) {
}

void UEndBattleAPI::SetHiddenBreakables(bool bHidden, const TArray<FName>& LevelNames, const TArray<FName>& AccessIDs) {
}

void UEndBattleAPI::SetHiddenBreakable(bool bHidden, FName LevelName, FName AccessID) {
}

void UEndBattleAPI::SetHeat(AEndCharacter* Character, bool Enable, float Duration) {
}

void UEndBattleAPI::SetForcedLODMode(AEndCharacter* Character, bool Enable) {
}

void UEndBattleAPI::SetForceActionRestriction(AEndCharacter* Character, bool forceActionRestriction) {
}

void UEndBattleAPI::SetEnableSlip(AEndCharacter* Character, bool Enable) {
}

void UEndBattleAPI::SetEnableSleepAnimationAttachCharacterOnly(AEndCharacter* Character, bool Enable) {
}

void UEndBattleAPI::SetEnableResidentBlend(AEndCharacter* Character, FName ResidentBlendName, bool bEnabled, float BlendTime) {
}

void UEndBattleAPI::SetEnableRegeneOfCharaParts(AEndCharacter* InCharacter, FName InPartsID, bool InEnable) {
}

void UEndBattleAPI::SetEnablePushCollision(AEndCharacter* Character, FName partId, bool Enable) {
}

void UEndBattleAPI::SetEnableEquipmentSkillFrogAlways(bool Enable, bool frogAfterDebuffDisable) {
}

void UEndBattleAPI::SetEnabledUpdateAimLocation(AEndCharacter* Character, bool bEnabled) {
}

void UEndBattleAPI::SetEnableControlDamageToParts(AEndCharacter* InCharacter, bool InDamageToOnePart) {
}

void UEndBattleAPI::SetEnableBreakPartsDamage(AEndCharacter* Character, FName BattleCharaPartsSpecID, bool Enable) {
}

void UEndBattleAPI::SetEnableBreakDamage(AEndCharacter* Character, bool Enable) {
}

void UEndBattleAPI::SetEnableBreakable(FName LevelName, FName AccessID, bool bEnable) {
}

void UEndBattleAPI::SetEnableBonamikGroup(AEndCharacter* Character, FName BonamikGroupName, bool bEnabled, float BlendTime) {
}

void UEndBattleAPI::SetEnableBonamikGroundCollision(AEndCharacter* Character, FName BonamikGroupName, bool bEnabled) {
}

void UEndBattleAPI::SetEnableBattleAway(bool Enable) {
}

void UEndBattleAPI::SetDyingAbilityID(AEndCharacter* Character, FName AbilityId) {
}

void UEndBattleAPI::SetDuringCommandAbilityInvalidPeriod(AEndCharacter* targetPlayerCharacter, bool bInvalid) {
}

void UEndBattleAPI::SetDrawPauseEnvironmentPhysicsActors(TArray<AActor*> objectList, bool drawPause, bool tickPause) {
}

void UEndBattleAPI::SetDrawPauseEnvironment(FName LevelName, FName AccessID, bool bPause, bool bIncludingCollision) {
}

void UEndBattleAPI::SetDrawPauseCharacter(AEndCharacter* Character, bool bPause) {
}

void UEndBattleAPI::SetDisperseTarget(AEndCharacter* Executor, AEndCharacter* TargetPlayer) {
}

void UEndBattleAPI::SetDisableTargetOfParts(AEndCharacter* Character, FName BattleCharaPartsSpecID, bool bDisableTarget) {
}

void UEndBattleAPI::SetDisableTargetNew(AEndCharacter* Character, bool Disable, bool showIcon) {
}

void UEndBattleAPI::SetDisableTarget(AEndCharacter* InChara, bool InDisable, bool hitDamage, bool refreshTargetLock) {
}

void UEndBattleAPI::SetDisableSummoning(bool Enable, int32 PhaseNumber) {
}

void UEndBattleAPI::SetDisableSubCollisionByGroupName(AEndCharacter* InChara, FName InGroupName, bool bDisable) {
}

void UEndBattleAPI::SetDisableSubCollision(AEndCharacter* InChara, bool bDisable) {
}

void UEndBattleAPI::SetDisableStealTextLabel(const FString& TextLabel) {
}

void UEndBattleAPI::SetDisableSteal(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisableReserveMemberCommand(bool Disable) {
}

void UEndBattleAPI::SetDisableReactionAndBreak(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisableReaction(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisablePartsBreak(AEndCharacter* Character, bool bDisable) {
}

void UEndBattleAPI::SetDisableParts(AEndCharacter* Character, FName BattleCharaPartsSpecID, bool bDisableTarget, bool bDisableDamage, bool bDisableDamageCollision) {
}

void UEndBattleAPI::SetDisableGameOver(bool Disable) {
}

void UEndBattleAPI::SetDisableFinish(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisableDeadDestroy(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisableDamageHit(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisableBurst(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDisableBodyHPDecrementByParts(AEndCharacter* Character, bool bDisable) {
}

void UEndBattleAPI::SetDisableBodyDamagePopupByParts(AEndCharacter* Character, bool bDisable) {
}

void UEndBattleAPI::SetDisableActionRestriction(AEndCharacter* Character, bool Disable) {
}

void UEndBattleAPI::SetDamageHitResponse(AEndCharacterBase* Character, bool bHitDamage) {
}

void UEndBattleAPI::SetCollisionEnableByComponentTag(AActor* InActor, bool bEnable, FName ComponentTag) {
}

void UEndBattleAPI::SetCharacterMovementMode(AEndCharacter* InChara, bool bMovable, bool bHitWall, bool bHitObject, bool bFitFloor, bool bMaxWeight) {
}

void UEndBattleAPI::SetCharacterBehaviorParts(AEndCharacter* Character, AEndCharacter* parentCharacter) {
}

void UEndBattleAPI::SetCharacterBehaviorMode(AEndCharacter* Character, EEndAnimBehaviorMode Mode, bool immediate) {
}

void UEndBattleAPI::SetBurstForceAerial(AEndCharacter* InChara, bool Flag) {
}

void UEndBattleAPI::SetBreakPartsDamageID(AEndCharacter* Character, FName BattleCharaPartsSpecID, FName BreakID) {
}

void UEndBattleAPI::SetBreakPartsDamage(AEndCharacter* Character, FName BattleCharaPartsSpecID, FName BreakID, float breakDamageHPMaxPercent) {
}

void UEndBattleAPI::SetBreakDamage(AEndCharacter* Character, FName BreakID, float breakDamageHPMaxPercent) {
}

void UEndBattleAPI::SetBPPercent(AEndCharacter* Character, float Value) {
}

void UEndBattleAPI::SetBPDamageCoefficient(AEndCharacter* Character, float Coefficient) {
}

void UEndBattleAPI::SetBP(AEndCharacter* Character, float Value) {
}

void UEndBattleAPI::SetBattleSceneCountLifeCycle(FName InName, EEndBattleSceneCountLifeCycleType InType, int32 InValue) {
}

void UEndBattleAPI::SetBattleSceneCount(FName InName, int32 InCount) {
}

void UEndBattleAPI::SetBattleSafeTransform(AEndCharacter* InChara, bool bEnable) {
}

void UEndBattleAPI::SetBattleAbilityRotateStatePointName(AEndCharacter* Character, FName PointName) {
}

void UEndBattleAPI::SetBattleAbilityRotateStateLocation(AEndCharacter* Character, const FVector& Location) {
}

void UEndBattleAPI::SetATBAll(float Value) {
}

void UEndBattleAPI::SetATB(EPlayerType PlayerType, float Value) {
}

void UEndBattleAPI::SetAIPCToSafeArea(EPlayerType PlayerCharacter, int32 GroupId, bool Flag, bool bIncludeReserve, bool bFollowUCPC, FVector AvoidLocation) {
}

void UEndBattleAPI::SetAIPCTargetDirect(const EPlayerType PlayerCharacter, AEndCharacter* TargetCharacter, TArray<FName> PartsIDList) {
}

void UEndBattleAPI::SetAIPCTargetChoosingParam(EPlayerType PlayerCharacter, TArray<ETargetChoosingTag> PriorityTagList, ETargetChoosingSort SortMethod, TArray<AEndCharacter*> AssignedTargets) {
}

void UEndBattleAPI::SetAIPCIgnoreHeight(EPlayerType PlayerType, bool InFlag) {
}

void UEndBattleAPI::SetAIPCExcludeTarget(EPlayerType PlayerType, AEndCharacter* TargetCharacter) {
}

void UEndBattleAPI::SetAIPCExcludeArea(const EPlayerType PlayerCharacter, int32 GroupId, const bool Flag, bool bIncludeReserve) {
}

void UEndBattleAPI::SetAIPCDisconnectArea(const AEndCharacter* InCharacter, int32 InGroupId) {
}

void UEndBattleAPI::SetAIPCConfrontIdle(EPlayerType InPlayerType, bool InFlag, bool bIncludeReserve) {
}

void UEndBattleAPI::SetAIPCCombatArea(const EPlayerType PlayerCharacter, int32 GroupId, const bool Flag, bool bIncludeReserve) {
}

void UEndBattleAPI::SetAimTargetOffsetHeight(AEndCharacter* Character, float OffsetHeight) {
}

void UEndBattleAPI::SetActorPause(AActor* Actor, bool bTickPause, bool bDrawPause) {
}

void UEndBattleAPI::SetActorMoveMode(AEndCharacter* Character, EActorMoveMode actorMoveMode) {
}

void UEndBattleAPI::SetActorLocationToRoot(AEndCharacter* Character, FVector NewLocation) {
}

void UEndBattleAPI::SetActorLocationAndRotationToRoot(AEndCharacter* Character, FVector NewLocation, FRotator NewRotator) {
}

void UEndBattleAPI::SendSystemMessage(const FString& InMessage) {
}

void UEndBattleAPI::SendPhaseNumberToSummonSystem(int32 currentPhase) {
}

void UEndBattleAPI::SendMetaMessage(const FString& InMessage) {
}

bool UEndBattleAPI::SendGenjiShieldToPlayBattleCamera(AEndCharacter* ownerCharacter, int32 sequenceActorUID) {
    return false;
}

void UEndBattleAPI::SendEventResidualParticles(AEndCharacter* ownerCharacter, EEndBattleResidualParticlesEventType EventType, bool otherThanOwner) {
}

void UEndBattleAPI::SendEventDamageSourceTheTableNumber(AEndCharacter* Character, FName DamageSourceID, int32 tableNumber) {
}

void UEndBattleAPI::SendEventDamageSource(AEndCharacter* Character, FName DamageSourceID) {
}

void UEndBattleAPI::RestrictBattleFieldBySummonBoss() {
}

void UEndBattleAPI::ResetWalkableFloorAngleOnBattleNav(AEndCharacter* InCharacter) {
}

void UEndBattleAPI::ResetWalkableFloorAngle(AEndCharacter* InCharacter) {
}

void UEndBattleAPI::ResetUniqueAbilityDerivedFixedAbilityID(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetSummonPointToIncreaseOneSecond() {
}

void UEndBattleAPI::ResetSummonCutSceneReturnLocation(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetSummonCondition() {
}

void UEndBattleAPI::ResetSubCollisionPushBackSpeed(AEndCharacter* InChara) {
}

void UEndBattleAPI::ResetRootCapsuleAttackTargetSizeScale(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetRigidBodyName(AEndCharacter* Character, FName RigidBodyName) {
}

void UEndBattleAPI::ResetPrimaryAnimPack(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetOverridePartsCameraLockSocketName(AEndCharacter* Character, FName BaseBattleCharaPartsSpecID, float BlendTime, EAlphaBlendOption BlendOption) {
}

void UEndBattleAPI::ResetOverrideMovementBase(AEndCharacter* InCharacter) {
}

void UEndBattleAPI::ResetOverrideLocomotionAnimSequenceName(AEndCharacter* InChara, EEndLocomotionAnimGroup AnimGroup, float BlendTime) {
}

void UEndBattleAPI::ResetOverrideKeep(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetOverrideEnemyBookID(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetOverrideCapsuleSize(AEndCharacter* InCharacter) {
}

void UEndBattleAPI::ResetOverrideCameraLockSocketName(AEndCharacter* Character, float BlendTime, EAlphaBlendOption BlendOption) {
}

void UEndBattleAPI::ResetOverrideBattleDefenseID(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetOverrideBattleCharaSpec(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetOverrideBattleCharaPartsSpec(AEndCharacter* Character, FName BaseID) {
}

void UEndBattleAPI::ResetOverrideAdditiveDamage(AEndCharacter* InChara) {
}

void UEndBattleAPI::ResetOverrideActiveAimAngle(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetHitCharaResponse(AEndCharacterBase* Character) {
}

void UEndBattleAPI::ResetDisperseTarget() {
}

void UEndBattleAPI::ResetDisableStealTextLabel() {
}

void UEndBattleAPI::ResetDamageHitResponse(AEndCharacterBase* Character) {
}

void UEndBattleAPI::ResetCharacterMovementMode(AEndCharacter* InChara) {
}

void UEndBattleAPI::ResetBreakWeakAttributeDamageValue(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetBreakPartsDamageValue(AEndCharacter* Character, FName BattleCharaPartsSpecID) {
}

void UEndBattleAPI::ResetBreakDamageValue(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetBP(AEndCharacter* Character, bool bResetAnimation) {
}

void UEndBattleAPI::ResetAppearanceFrog(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetAppearance(AEndCharacter* Character) {
}

void UEndBattleAPI::ResetAIPCTargetDirect(const EPlayerType PlayerCharacter) {
}

void UEndBattleAPI::ResetAIPCTargetChoosingParam(const EPlayerType PlayerCharacter) {
}

void UEndBattleAPI::ResetAIPCExcludeTarget(EPlayerType PlayerType) {
}

void UEndBattleAPI::ResetAIPCDisconnectArea() {
}

void UEndBattleAPI::ResetAimTargetOffsetHeight(AEndCharacter* Character) {
}

bool UEndBattleAPI::RequestUniqueAbilitySpawnWeapon(AEndCharacter* ownerCharacter, EEndBattleUniqueAbilitySpawnWeaponType weaponType, EEndBattleSpawnWeaponStateType weaponStateType, FName uniqueWeaponName) {
    return false;
}

void UEndBattleAPI::RequestSyncActionEnd(AEndCharacter* Chara, EEndBattleSyncActionEndType Type, AEndCharacter* causerCharacter) {
}

bool UEndBattleAPI::RequestSummonEnemyPreloadCutSceneAbility(AEndCharacter* InCharacter, FName InCutSceneID, FName InDamageSourceID) {
    return false;
}

bool UEndBattleAPI::RequestSummonEnemyPlayCutSceneAbility(AEndCharacter* InCharacter) {
    return false;
}

bool UEndBattleAPI::RequestSummonEnemyCutSceneAbility(AEndCharacter* InCharacter, FName InCutSceneID, FName InDamageSourceID) {
    return false;
}

void UEndBattleAPI::RequestShowAbilityName(AEndCharacter* Character, const FString& String, float InTime, bool bNonGuardableIcon) {
}

void UEndBattleAPI::RequestReturnSummon() {
}

void UEndBattleAPI::RequestPreloadCutScene(FName CutSceneID) {
}

bool UEndBattleAPI::RequestCurrentChargeCrystalDisappears(AEndCharacter* ownerCharacter) {
    return false;
}

bool UEndBattleAPI::RequestCreateDestructionParts(AEndCharacter* ownerCharacter, FName uniqueName, FName spawnCharaSpecName, FName partsAttachSocketName, bool recreate) {
    return false;
}

bool UEndBattleAPI::RequestBrokenDestructionParts(AEndCharacter* ownerCharacter, FName uniqueName) {
    return false;
}

void UEndBattleAPI::RequestAttachSyncAction(AEndCharacter* Character) {
}

void UEndBattleAPI::RepairParts(AEndCharacter* Character, FName BattleCharaPartsSpecID, FName MeshLabel, EEndPartsRepairConditionType Condition) {
}

void UEndBattleAPI::RemoveStatusChangeID(AEndCharacter* Character, FName statusChangeID, bool Lock) {
}

void UEndBattleAPI::RemoveSpecialStatusChangeType(AEndCharacter* InChara, EEndBattleSpecialStatusChangeType InType) {
}

void UEndBattleAPI::RemoveSpecialStatusChangeIDRequest(AEndCharacter* Character, FName ID) {
}

void UEndBattleAPI::RemoveSpecialStatusChangeID(AEndCharacter* Character, FName ID) {
}

void UEndBattleAPI::RemoveSpecialStateEffect(AEndCharacter* Character, FName specialStateEffectID) {
}

void UEndBattleAPI::RemoveIgnoreDamageSourceLookAtTraceActor(AEndCharacter* Character, AActor* IgnoreActor) {
}

void UEndBattleAPI::RemoveDangerSource(AEndCharacter* Instigator, EEndAISensorDangerObjectType Type) {
}

void UEndBattleAPI::RemoveAttachEffect(AEndCharacter* Chara, const FName AttachSocketName, const FName ResourceName, bool bDestroy) {
}

void UEndBattleAPI::ReleaseBattleFieldBySummonBoss() {
}

void UEndBattleAPI::ReGuard(AEndCharacter* Character) {
}

bool UEndBattleAPI::RegisterTargetLockGroup(AEndCharacter* Character, const TArray<AEndCharacter*>& TargetList, int32 MaxEachTargetNum, bool bPrioritizeUCPC, FName GroupName, EEndBattleAITargetLockGroupPriority Priority, bool bIgnoreProvocation, bool bNoLockLastOne) {
    return false;
}

void UEndBattleAPI::RaycastWallFromChara(AEndCharacter* InCharacter, float InOffsetYaw, float InCastRange, bool& OutHit, float& OutDistance, FHitResult& OutParam) {
}

bool UEndBattleAPI::RaycastTerrainFromChara(FHitResult& HitResult, AEndCharacter* Character, FName SocketName, FVector Offset, TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime) {
    return false;
}

void UEndBattleAPI::RaycastSphereWallFromChara(AEndCharacter* InCharacter, float InOffsetYaw, float InCastRange, float InRadius, bool& OutHit, float& OutDistance, FHitResult& OutParam) {
}

void UEndBattleAPI::PlayPartStartLoopEndMotion(AEndCharacter* Character, FName StartMotionName, FName LoopMotionName, FName endMotionName, FName BoneName, EEndExtraActionLayer Layer, float LoopTime) {
}

void UEndBattleAPI::PlayPartMotion(AEndCharacter* Character, FName MotionName, FName BoneName, EEndExtraActionLayer Layer, float overrideBlendIn, float overrideBlendOut) {
}

void UEndBattleAPI::PlayPartLoopMotion(AEndCharacter* Character, FName MotionName, FName BoneName, EEndExtraActionLayer Layer) {
}

void UEndBattleAPI::PlayInterruptAnimInBurst(AEndCharacter* InChara) {
}

int32 UEndBattleAPI::PlayEffectFromResourceCharacter(int32 CategoryType, AActor* ResourceActor, FName ResourceName, AActor* AttachActor, FName AttachSocketName, bool NotSynchronizeInvisible) {
    return 0;
}

int32 UEndBattleAPI::PlayEffect(int32 CategoryType, FName ResourceName, AActor* AttachActor, FName AttachSocketName, bool NotSynchronizeInvisible) {
    return 0;
}

bool UEndBattleAPI::PlayDitherFadeEffect(int32 CategoryType, FName ResourceName, AEndCharacter* ownerCharacter, FName AttachSocketName) {
    return false;
}

void UEndBattleAPI::PlayCrowdActor(FName LevelName, FName AccessID, float BlendTime, bool bUseFade) {
}

int32 UEndBattleAPI::PlayBattleCameraSequenceSpecialSkill(FName CameraSequenceID, AEndCharacterBase* OwnerChara, AEndCharacterBase* HasResourceChara, AActor* TargetActor) {
    return 0;
}

int32 UEndBattleAPI::PlayBattleCameraSequence(FName CameraSequenceID, AEndCharacterBase* OwnerChara, AEndCharacterBase* HasResourceChara, AActor* TargetActor, bool bIsToRegisterSlaveViewOnly, float MassiveEnvironmentFrustrumScaleForMainPass) {
    return 0;
}

void UEndBattleAPI::PlayAnimEnvironmentBeginLoop(FName LevelName, FName AccessID, FName BeginAnimName, FName LoopAnimName) {
}

void UEndBattleAPI::PlayAnimEnvironment(FName LevelName, FName AccessID, FName AnimName, EEndBattleEnvironmentAnimPlayType PlayType) {
}

void UEndBattleAPI::PlayAddMotion(AEndCharacter* Character, FName MotionName, EEndExtraActionLayer Layer, bool bInfiniteLoop) {
}

void UEndBattleAPI::OverrideSummonPointToIncreaseOneSecond(float Point) {
}

void UEndBattleAPI::OverrideSummonCutSceneReturnLocation(AEndCharacter* Character, FTransform Transform) {
}

void UEndBattleAPI::OverrideSummonCaptureTimeLimit(float Time) {
}

void UEndBattleAPI::OverrideDamageSourceIDCutSceneAbility(AEndCharacter* InCharacter, FName InDamageSourceID) {
}

void UEndBattleAPI::OnSummonFinishActivatePhase() {
}

void UEndBattleAPI::OnSummonActivateTriggerAction() {
}

void UEndBattleAPI::NotifyAbilityReaction(AEndCharacter* Character, float Param0) {
}

bool UEndBattleAPI::NavmeshRaycastFromChara(AEndCharacter* InCharacter, float InOffsetYaw, float& OutDistance, float InCastRange, bool InForceSSizeNav, bool InDrawDebug, float InDrawDebugTime, bool NoCheckEscapeWall) {
    return false;
}

bool UEndBattleAPI::NavmeshRaycast(FVector InLocation, FVector InDirection, float& OutDistance, AEndCharacterBase* InExecutor, float InCastRange, bool InDrawDebug, float InDrawDebugTime, bool NoCheckEscapeWall) {
    return false;
}

void UEndBattleAPI::MoveGenjiShield(AEndCharacter* ownerCharacter, AEndCharacter* causerCharacter) {
}

bool UEndBattleAPI::IsUniqueAbility(FName AbilityId) {
    return false;
}

bool UEndBattleAPI::IsUCPC(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsSummonGaugeZero() {
    return false;
}

bool UEndBattleAPI::IsSummon(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsSetRigidBodyName(AEndCharacter* Character, FName RigidBodyName) {
    return false;
}

bool UEndBattleAPI::IsRideFatMoogle(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsPlayingBattleCameraSequence(int32 sequenceActorUID) {
    return false;
}

bool UEndBattleAPI::IsPlayingAnimEnvironment(FName LevelName, FName AccessID, FName AnimName) {
    return false;
}

bool UEndBattleAPI::IsPlayerCharacterValid(EPlayerType Type) {
    return false;
}

bool UEndBattleAPI::IsPlayer(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsOverlapPoint(AEndNavModifierVolume* InVolume, FVector InPoint) {
    return false;
}

bool UEndBattleAPI::IsOverlapCharaFromName(FName InVolumeName, AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsNormal(FName InAbilityName) {
    return false;
}

bool UEndBattleAPI::IsMagic(FName InAbilityName) {
    return false;
}

bool UEndBattleAPI::IsLimit(FName InAbilityName) {
    return false;
}

bool UEndBattleAPI::IsLaunchActionPlaying(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsLaunchActionInAir(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsItem(FName InAbilityName) {
    return false;
}

bool UEndBattleAPI::IsInSyncAction(AEndCharacter* Chara) {
    return false;
}

bool UEndBattleAPI::IsInSupportField(AEndCharacter* Character, EEndBattleSupportFieldType supportFieldType) {
    return false;
}

bool UEndBattleAPI::IsInSummonCutScene() {
    return false;
}

bool UEndBattleAPI::IsInScreen(AActor* Actor) {
    return false;
}

bool UEndBattleAPI::IsInFanRange(AEndCharacter* ownerCharacter, float baseYaw, float angleRange, float radiusMin, float radiusMax, FVector targetPosition) {
    return false;
}

bool UEndBattleAPI::IsInEnemySummonCutScene() {
    return false;
}

bool UEndBattleAPI::IsInBattle() {
    return false;
}

bool UEndBattleAPI::IsHPPercent(AEndCharacter* InChara, int32 Percent, EEndAiMathCmp Cmp) {
    return false;
}

bool UEndBattleAPI::IsGuard(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsFillLimitPlayer(FName PlayerCharaName) {
    return false;
}

bool UEndBattleAPI::IsDummyPartyMember(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsDodgeResetUniqueAbility(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsDisperseTargetExecutor(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsDisableTarget(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsDamageSourceFlagDisableFinish(int64 Flag) {
    return false;
}

bool UEndBattleAPI::IsDamage(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsContainedMotionListArray(AEndCharacter* InChara, const TArray<FName>& InMot) {
    return false;
}

bool UEndBattleAPI::IsContainedMotionList5(AEndCharacter* InChara, FName InMot1, FName InMot2, FName InMot3, FName InMot4, FName InMot5) {
    return false;
}

bool UEndBattleAPI::IsContainedMotionList4(AEndCharacter* InChara, FName InMot1, FName InMot2, FName InMot3, FName InMot4) {
    return false;
}

bool UEndBattleAPI::IsContainedMotionList3(AEndCharacter* InChara, FName InMot1, FName InMot2, FName InMot3) {
    return false;
}

bool UEndBattleAPI::IsContainedMotionList2(AEndCharacter* InChara, FName InMot1, FName InMot2) {
    return false;
}

bool UEndBattleAPI::IsContainedMotionList(AEndCharacter* InChara, FName InMot1) {
    return false;
}

bool UEndBattleAPI::IsCommandAbilityCombination(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsCombinationAbilityFromDataObjectBattleAbility(int64 Flag0) {
    return false;
}

bool UEndBattleAPI::IsCloudOffensiveMode() {
    return false;
}

bool UEndBattleAPI::IsCharaID(AEndCharacter* InChara, const FName Upper, const FName Lower) {
    return false;
}

void UEndBattleAPI::IsCharacterValidBranch(AEndCharacter* InCharacter, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal) {
}

bool UEndBattleAPI::IsCharacterValid(AEndCharacter* InCharacter) {
    return false;
}

bool UEndBattleAPI::IsBurst(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsBrokenParts(AEndCharacter* Character, FName BattleCharaPartsSpecID) {
    return false;
}

bool UEndBattleAPI::IsBreakEndAction(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsBreak(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsAIPCRangedWeaponEquipped(const EPlayerType PlayerCharacter) {
    return false;
}

bool UEndBattleAPI::IsAIPC(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsAdditiveDamagePlaying(AEndCharacter* InChara) {
    return false;
}

bool UEndBattleAPI::IsActionRestriction(AEndCharacter* Character) {
    return false;
}

bool UEndBattleAPI::IsAbility(FName InAbilityName) {
    return false;
}

void UEndBattleAPI::InvalidNearFadeEnvPhysicsActor() {
}

int32 UEndBattleAPI::IncBattleSceneCount(FName InName) {
    return 0;
}

void UEndBattleAPI::HidePhysics(FName ActorName) {
}

void UEndBattleAPI::HideAbilityName(AEndCharacter* Character) {
}

bool UEndBattleAPI::HasStatusChangeID(AEndCharacter* Character, FName statusChangeID) {
    return false;
}

bool UEndBattleAPI::HasSpecialStatusChangeType(AEndCharacter* InChara, EEndBattleSpecialStatusChangeType InType) {
    return false;
}

bool UEndBattleAPI::HasSpecialStatusChangeID(AEndCharacter* Character, FName ID) {
    return false;
}

bool UEndBattleAPI::HasDamageSource(AEndCharacter* InChara, FName InDamageSourceID) {
    return false;
}

bool UEndBattleAPI::HasAbilityElement(FName InAbilityName, EEndBattleAttributeType InType) {
    return false;
}

float UEndBattleAPI::GetWorldLocationAngle(const FVector& BaseLocation, const FVector& TargetLocation) {
    return 0.0f;
}

void UEndBattleAPI::GetTrophyFirstRescue() {
}

float UEndBattleAPI::GetTargetLocationAngle(AEndCharacter* Character, FVector TargetLocation) {
    return 0.0f;
}

float UEndBattleAPI::GetTargetCharacterAngle(AEndCharacter* Character, AEndCharacter* TargetCharacter) {
    return 0.0f;
}

AEndCharacter* UEndBattleAPI::GetTargetCharacter(AEndCharacter* Character) {
    return NULL;
}

FName UEndBattleAPI::GetSyncActionIDLast(AEndCharacter* Chara) {
    return NAME_None;
}

FName UEndBattleAPI::GetSyncActionID(AEndCharacter* Chara) {
    return NAME_None;
}

AEndBattleSummonTargetPoint* UEndBattleAPI::GetSummonTargetPointFromActorName(FName InActorName) {
    return NULL;
}

float UEndBattleAPI::GetSummonAvilableTime() {
    return 0.0f;
}

AEndCharacter* UEndBattleAPI::GetSummom(EEndBattleSummonType Type) {
    return NULL;
}

float UEndBattleAPI::GetSubCollisionPushBackSpeed(AEndCharacter* InChara) {
    return 0.0f;
}

int32 UEndBattleAPI::GetStoryFlagConditionNum(TArray<FName> storyFlagNames, bool Condition, int32 initializeNum) {
    return 0;
}

int32 UEndBattleAPI::GetSpendATBBarTotal(AEndCharacter* EndCharacter) {
    return 0;
}

void UEndBattleAPI::GetSpecialStatusChangeType(AEndCharacter* Character, TArray<EEndBattleSpecialStatusChangeType>& typeList) {
}

float UEndBattleAPI::GetSpecialStatusChangeParamFloat(AEndCharacter* Character, EEndBattleSpecialStatusChangeType Type, FName paramID) {
    return 0.0f;
}

FTransform UEndBattleAPI::GetSocketTransform(AEndCharacter* InChara, FName InSocketName) {
    return FTransform{};
}

AEndCharacter* UEndBattleAPI::GetRiddenMasterCharacter(AEndCharacter* Character) {
    return NULL;
}

int32 UEndBattleAPI::GetResistanceElement(AEndCharacter* InChara, int32 InType) {
    return 0;
}

FName UEndBattleAPI::GetReplaceDamageSourceID(FName InAbilityName) {
    return NAME_None;
}

FName UEndBattleAPI::GetRaceName(AEndCharacter* InChara) {
    return NAME_None;
}

void UEndBattleAPI::GetPlayingExtraActionSequenceNames(TArray<FName>& OutNames, AEndCharacter* InChara) {
}

EPlayerType UEndBattleAPI::GetPlayerType(AEndCharacter* InChara) {
    return EPlayerType::CLOUD;
}

AEndCharacter* UEndBattleAPI::GetPlayerCharacter(EPlayerType Type) {
    return NULL;
}

TArray<AActor*> UEndBattleAPI::GetPhysicsInVolumeFromLocation(FName InVolumeName, FName LocationName, FName InName, bool InContain, bool InPossetion, bool InCanPosettion) {
    return TArray<AActor*>();
}

TArray<AActor*> UEndBattleAPI::GetPhysicsInVolume(FName InVolumeName, FName InName, bool InContain, bool InPossetion) {
    return TArray<AActor*>();
}

TArray<AEndEnvironmentPhysicsStaticMeshActor*> UEndBattleAPI::GetPhysicsFromLocation(FName LocationName) {
    return TArray<AEndEnvironmentPhysicsStaticMeshActor*>();
}

TArray<AActor*> UEndBattleAPI::GetPhysicsFromActorName(FName InName, bool InContain) {
    return TArray<AActor*>();
}

int32 UEndBattleAPI::GetPhysicsDefense(AEndCharacter* InChara) {
    return 0;
}

int32 UEndBattleAPI::GetPhysicsAttack(AEndCharacter* Character) {
    return 0;
}

TArray<AActor*> UEndBattleAPI::GetPhysics(FName InName, bool InContain) {
    return TArray<AActor*>();
}

TArray<AEndCharacter*> UEndBattleAPI::GetPartyMembersIgnoreDead() {
    return TArray<AEndCharacter*>();
}

AEndCharacter* UEndBattleAPI::GetPartyLeader() {
    return NULL;
}

int32 UEndBattleAPI::GetPartsHPPercent(AEndCharacter* Character, FName BattleCharaPartsSpecID) {
    return 0;
}

TArray<AEndNavModifierVolume*> UEndBattleAPI::GetOverlapVolumes(AEndCharacter* InChara) {
    return TArray<AEndNavModifierVolume*>();
}

FTransform UEndBattleAPI::GetOffsetTransform(const FTransform& Transform, const FVector& Offset, TEnumAsByte<GetOffsetTransform::Type> RotationType) {
    return FTransform{};
}

FName UEndBattleAPI::GetNearestTargetPointName(FVector BaseLocation, TArray<FName> targetPointNameList) {
    return NAME_None;
}

FName UEndBattleAPI::GetNearestSocketName(FVector BaseLocation, TArray<FName> SocketNameList, AEndCharacter* HasSocketNameChara) {
    return NAME_None;
}

AEndCharacter* UEndBattleAPI::GetNearestRangePartyCharacter(AEndCharacter* InChara, float Range, bool ZVisible) {
    return NULL;
}

AActor* UEndBattleAPI::GetNearestPhysicsInVolumeFromLocation(AEndCharacter* InChara, FName InVolumeName, FName LocationName, FName InName, bool InContain, bool InPossetion, bool InCanPosettion) {
    return NULL;
}

AActor* UEndBattleAPI::GetNearestPhysicsInVolume(AEndCharacter* InChara, FName InVolumeName, FName InName, bool InContain, bool InPossetion) {
    return NULL;
}

AActor* UEndBattleAPI::GetNearestPhysicsFromActorName(AEndCharacter* InChara, FName InName, bool InContain) {
    return NULL;
}

AActor* UEndBattleAPI::GetNearestPhysics(AEndCharacter* InChara, FName InName, bool InContain) {
    return NULL;
}

FVector UEndBattleAPI::GetNearestOwnVolumeWithExtent(AEndCharacter* InChara, FVector InLocation, FVector InExtent) {
    return FVector{};
}

FVector UEndBattleAPI::GetNearestOwnVolume(AEndCharacter* InChara, FVector InLocation) {
    return FVector{};
}

AEndCharacter* UEndBattleAPI::GetNearestCharacter(FVector InLocation, TArray<AEndCharacter*> InList) {
    return NULL;
}

void UEndBattleAPI::GetNearestActor(AActor*& outActor, AActor* baseActor, const TArray<AActor*>& compareActorList, const TArray<AActor*>& ignoreActorList) {
}

TArray<AEndNavModifierVolume*> UEndBattleAPI::GetNavVolumeFromType(FName InBattleSceneID, TEnumAsByte<EModifierVolumeType::Type> InType) {
    return TArray<AEndNavModifierVolume*>();
}

AEndNavModifierVolume* UEndBattleAPI::GetNavVolumeFromAngle(AEndCharacter* InChara, float InAngleRange, EEndBattleCompareDistanceType InType, int32 InGroup, bool InBehind) {
    return NULL;
}

TArray<FName> UEndBattleAPI::GetMotionList(AEndCharacter* InChara) {
    return TArray<FName>();
}

bool UEndBattleAPI::GetMateriaParam(AEndCharacter* InChara, bool bWeapon, int32 Slot, FEndBattleMateriaParam& Param) {
    return false;
}

int32 UEndBattleAPI::GetMagicDefense(AEndCharacter* InChara) {
    return 0;
}

int32 UEndBattleAPI::GetMagicAttack(AEndCharacter* Character) {
    return 0;
}

FTransform UEndBattleAPI::GetLayoutTransform(FName NodeName) {
    return FTransform{};
}

int32 UEndBattleAPI::GetKeep(AEndCharacter* InChara) {
    return 0;
}

int32 UEndBattleAPI::GetHPPercent(AEndCharacter* InChara) {
    return 0;
}

int32 UEndBattleAPI::GetHPMax(AEndCharacter* Character) {
    return 0;
}

EEndBattleCharaCategoryType UEndBattleAPI::GetHighestPriorityBattleCharaCategory(const FName& territoryID) {
    return EEndBattleCharaCategoryType::Normal;
}

bool UEndBattleAPI::GetHiddenBreakable(FName LevelName, FName AccessID) {
    return false;
}

float UEndBattleAPI::GetGuardTime(AEndCharacter* InChara) {
    return 0.0f;
}

bool UEndBattleAPI::GetFirstDamageTime(float& FirstDamageTime, const UAnimSequence* AnimSequecne, float StartTime) {
    return false;
}

AActor* UEndBattleAPI::GetFarestPhysics(AEndCharacter* InChara, float InRadius, FName InName, bool InContain) {
    return NULL;
}

AEndCharacter* UEndBattleAPI::GetFarestCharacter(FVector InLocation, TArray<AEndCharacter*> InList) {
    return NULL;
}

void UEndBattleAPI::GetFarestActor(AActor*& outActor, AActor* baseActor, const TArray<AActor*>& compareActorList, const TArray<AActor*>& ignoreActorList) {
}

int32 UEndBattleAPI::GetExpectationCountInConeAreaByLocation(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float ConeRadius, float ConeAngle, FVector TargetLocation, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime) {
    return 0;
}

int32 UEndBattleAPI::GetExpectationCountInConeArea(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float ConeRadius, float ConeAngle, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime) {
    return 0;
}

int32 UEndBattleAPI::GetExpectationCountInCapsuleAreaByLocation(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float CapsuleRadius, float CapsuleLength, FVector TargetLocation, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime) {
    return 0;
}

int32 UEndBattleAPI::GetExpectationCountInCapsuleArea(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float CapsuleRadius, float CapsuleLength, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime) {
    return 0;
}

FTransform UEndBattleAPI::GetEnvironmentSocketTransform(FName LevelName, FName AccessID, FName SocketName) {
    return FTransform{};
}

EEndEnemyTerritorySituationType UEndBattleAPI::GetEnemyTerritorySituationType(const FName& territoryID) {
    return EEndEnemyTerritorySituationType::None;
}

void UEndBattleAPI::GetEnemyMembersRef(TArray<AEndCharacter*>& Out) {
}

TArray<AEndCharacter*> UEndBattleAPI::GetEnemyMembersFromID(FName Upper, FName Lower, bool Flip) {
    return TArray<AEndCharacter*>();
}

AEndCharacter* UEndBattleAPI::GetEnemyMemberFromIDWithIndex(FName Upper, FName Lower, int32 InIndex) {
    return NULL;
}

int32 UEndBattleAPI::GetEnemyMemberCountFromID(FName Upper, FName Lower, bool Flip) {
    return 0;
}

int32 UEndBattleAPI::GetEnemyMemberCount(FName ContainRaceID) {
    return 0;
}

TArray<FName> UEndBattleAPI::GetEncountBattleSceneIDs() {
    return TArray<FName>();
}

bool UEndBattleAPI::GetEnableBreakable(FName LevelName, FName AccessID) {
    return false;
}

TArray<AEndCharacter*> UEndBattleAPI::GetDummyPartyMembers() {
    return TArray<AEndCharacter*>();
}

TArray<AEndCharacter*> UEndBattleAPI::GetDummyNPCsFromID(FName Upper, FName Lower) {
    return TArray<AEndCharacter*>();
}

TArray<AEndCharacter*> UEndBattleAPI::GetDummyEnemies() {
    return TArray<AEndCharacter*>();
}

bool UEndBattleAPI::GetDataObjectBattleDamageSourceFromAbilityID(FName AbilityId, FEndDataObjectBattleDamageSourceAccessor& dataObjectBattleDamageSource) {
    return false;
}

bool UEndBattleAPI::GetDataObjectBattleDamageSource(FName DamageSourceID, FEndDataObjectBattleDamageSourceAccessor& dataObjectBattleDamageSource) {
    return false;
}

bool UEndBattleAPI::GetDataObjectBattleAbility(FName AbilityId, FEndDataObjectBattleAbilityAccessor& dataObjectBattleAbility) {
    return false;
}

TArray<FVector> UEndBattleAPI::GetDamageSourceLocations(TArray<FName> DamageSourceIDs, AEndCharacter* ownerCharacter) {
    return TArray<FVector>();
}

int32 UEndBattleAPI::GetDamageSourceCountInArea(FName InDamageSourceID, AActor* ActorToSearchAround, float SearchRadius, bool bFlatSearch) {
    return 0;
}

int32 UEndBattleAPI::GetDamageSourceCount(FName InDamageSourceID) {
    return 0;
}

uint8 UEndBattleAPI::GetDamageHitReactionTableIndex(AEndCharacter* Character) {
    return 0;
}

EEndLocomotionState UEndBattleAPI::GetCurrentLocomotionState(AEndCharacter* InChara) {
    return EEndLocomotionState::Idle;
}

FName UEndBattleAPI::GetCurrentAbilityID(AEndCharacter* InChara) {
    return NAME_None;
}

FVector UEndBattleAPI::GetCompareLocation(FVector BaseLocation, const TArray<FVector>& compareLocationList, bool bCompare2D, EEndBattleCompareLocationType compareType) {
    return FVector{};
}

FName UEndBattleAPI::GetCombinationAbilityUsedCharacterName(FName AbilityId) {
    return NAME_None;
}

FName UEndBattleAPI::GetCharaSpecName(AEndCharacter* Character) {
    return NAME_None;
}

FName UEndBattleAPI::GetCharaID(AEndCharacter* InChara) {
    return NAME_None;
}

int32 UEndBattleAPI::GetCharaHP(AEndCharacter* InChara) {
    return 0;
}

AEndCharacter* UEndBattleAPI::GetCharaFromRaceID(FName InRaceName) {
    return NULL;
}

AEndCharacter* UEndBattleAPI::GetCharaFromActorName(FName InActorName, bool bAllowFindCharaPopManager) {
    return NULL;
}

EEndCharacterControllerStateType UEndBattleAPI::GetCharacterStateType(AEndCharacter* Character) {
    return EEndCharacterControllerStateType::None;
}

void UEndBattleAPI::GetCharactersFromID(FName Upper, FName Lower, TArray<AEndCharacter*>& OutList, TArray<AEndCharacter*> InList) {
}

int32 UEndBattleAPI::GetCharacterNameSymbolIndex(AEndCharacter* Character) {
    return 0;
}

float UEndBattleAPI::GetBreakTime(AEndCharacter* Character) {
    return 0.0f;
}

float UEndBattleAPI::GetBPPercent(AEndCharacter* Character) {
    return 0.0f;
}

float UEndBattleAPI::GetBP(AEndCharacter* Character) {
    return 0.0f;
}

FName UEndBattleAPI::GetBattleSceneIDFromChara(AEndCharacter* InChara, bool InParent) {
    return NAME_None;
}

int32 UEndBattleAPI::GetBattleSceneCount(FName InName) {
    return 0;
}

int32 UEndBattleAPI::GetBattleMemberConditionList(bool dead, bool sleep, bool Stop, bool petrify, bool Toad, TArray<AEndCharacter*>& MemberList) {
    return 0;
}

FName UEndBattleAPI::GetBattleCharaSpec_DataTableID(AEndCharacter* InChara) {
    return NAME_None;
}

FName UEndBattleAPI::GetBattleCameraSequenceID(int32 sequenceActorUID) {
    return NAME_None;
}

void UEndBattleAPI::GetAttackableCharacters(TArray<AEndCharacter*>& OutList, TArray<AEndCharacter*> InList) {
}

TArray<FVector> UEndBattleAPI::GetAllDamageSourceLocations(FName DamageSourceID) {
    return TArray<FVector>();
}

AEndAIControllerBluePrintBase* UEndBattleAPI::GetAIController(AEndCharacter* InChara) {
    return NULL;
}

FName UEndBattleAPI::GetActorName(AEndCharacter* InChara) {
    return NAME_None;
}

float UEndBattleAPI::GetActorDistance(AActor* From, AActor* To) {
    return 0.0f;
}

FVector UEndBattleAPI::GetActorDirection(AActor* From, AActor* To) {
    return FVector{};
}

int32 UEndBattleAPI::GetAbilityElement(FName InAbilityName) {
    return 0;
}

void UEndBattleAPI::GameOverForce() {
}

void UEndBattleAPI::ForceDisableAimEffectorSetting(AEndCharacter* Character, FName EffectorSettingName) {
}

void UEndBattleAPI::ForceDestroyParts(AEndCharacter* ownerCharacter, FName uniqueName) {
}

void UEndBattleAPI::FinishSummonOmenEffect() {
}

TArray<AEndNavModifierVolume*> UEndBattleAPI::FindNavVolumesOutRange(AEndCharacter* Character, TArray<int32> Groups, float angleRange, EEndBattleCompareDistanceType Type, bool behind, float Distance) {
    return TArray<AEndNavModifierVolume*>();
}

TArray<AEndNavModifierVolume*> UEndBattleAPI::FindNavVolumesInRange(AEndCharacter* Character, TArray<int32> Groups, float angleRange, EEndBattleCompareDistanceType Type, bool behind, float Distance) {
    return TArray<AEndNavModifierVolume*>();
}

bool UEndBattleAPI::FindEnableCrystalAppearPoint(AEndCharacter* ownerCharacter, float nearLength, float farLength, float viewAngle, FName& outPointName, FTransform& outPointTransform) {
    return false;
}

bool UEndBattleAPI::ExistsNavmeshWallEdgeFromChara(AEndCharacter* InCharacter, float& OutDistance, float InRadius, bool InForceSSizeNav, bool InDrawDebug, float InDrawDebugTime) {
    return false;
}

bool UEndBattleAPI::ExistsNavmeshWallEdge(FVector InLocation, float& OutDistance, AEndCharacterBase* InExecutor, float InRadius, bool InDrawDebug, float InDrawDebugTime) {
    return false;
}

bool UEndBattleAPI::ExistDamageSourceRevive() {
    return false;
}

void UEndBattleAPI::ExcludeActorsFromSkillCameraSlow(int32 sequenceActorUID, TArray<AActor*> Actors) {
}

void UEndBattleAPI::ExcludeActorFromSkillCameraSlow(int32 sequenceActorUID, AActor* Actor) {
}

void UEndBattleAPI::EndForceFieldMode() {
}

void UEndBattleAPI::EndBurst(AEndCharacter* Character, bool instant) {
}

void UEndBattleAPI::EndBreakTime(AEndCharacter* Character, bool immediatelyEndAction) {
}

void UEndBattleAPI::EndBattleDirection() {
}

void UEndBattleAPI::EnableDamageReactionOwnerSyncAction(AEndCharacter* Character) {
}

bool UEndBattleAPI::Die(AEndCharacter* Character, AEndCharacter* causerCharacter, bool skipDirection) {
    return false;
}

void UEndBattleAPI::DestroySupportFieldAll() {
}

void UEndBattleAPI::DestroySafeAreaBehindDamageSource(int32 InGroupId, const TArray<FName>& InDamageSourceIdList) {
}

void UEndBattleAPI::DestroyDamageSourceAllCharacter(AEndCharacter* Character, bool bDestroyEffect, bool forceDestroy) {
}

void UEndBattleAPI::DestroyDamageSourceAll(bool bDestroyEffect) {
}

void UEndBattleAPI::DestroyDamageSource(FName DamageSourceID, AEndCharacter* ownerCharacter, bool bDestroyEffect, bool forceDestroy) {
}

int32 UEndBattleAPI::DecBattleSceneCount(FName InName) {
    return 0;
}

void UEndBattleAPI::DebugSetPropertyInformation(AEndCharacter* InCharacter, const FString& InName) {
}

void UEndBattleAPI::DebugSetHP(AEndCharacter* Chara, int32 HP) {
}

void UEndBattleAPI::CreateSyncActionOwnersByName(FName syncActionID0, FName ownerCharaName0, FName syncActionID1, FName ownerCharaName1, FName syncActionID2, FName ownerCharaName2) {
}

void UEndBattleAPI::CreateSyncActionOwners(FName syncActionID0, AEndCharacter* ownerChara0, FName syncActionID1, AEndCharacter* ownerChara1, FName syncActionID2, AEndCharacter* ownerChara2) {
}

void UEndBattleAPI::CreateSyncAction(FName SyncActionID, AEndCharacter* OwnerChara, AEndCharacter* targetChara, bool bPlayFromLoop, bool bOverwrite) {
}

void UEndBattleAPI::CreateSafeAreaBehindDamageSource(int32 InGroupId, const TArray<FName>& InDamageSourceIdList, AActor* InDangerActor) {
}

void UEndBattleAPI::CreateDamageSource(FName DamageSourceID, AEndCharacter* ownerCharacter, AEndCharacter* TargetCharacter, FName AbilityId, bool bOverrideDamage, int32 OverrideDamage) {
}

void UEndBattleAPI::CloseSummonEnvironment() {
}

void UEndBattleAPI::ClearEffectsByCategoryBattle() {
}

void UEndBattleAPI::ClearBPDamageCoefficient(AEndCharacter* Character) {
}

void UEndBattleAPI::ClearBattleCameraRestrictedPlayOwners() {
}

void UEndBattleAPI::ChangePositionOfSummonOmen(int32 PhaseNumber, AEndCharacter* ownerCharacter) {
}

void UEndBattleAPI::ChangePartyMember(TArray<FEndMenuJoin> changeParameters, bool showUI) {
}

void UEndBattleAPI::ChangeAppearance(AEndCharacter* Character, int32 Index) {
}

bool UEndBattleAPI::CanSyncAction(AEndCharacter* Chara) {
    return false;
}

float UEndBattleAPI::CalcAimTargetOffsetHeight(FVector From, FVector To, float Velocity, float GravityScale, bool bDebugDraw, float DebugDrawTime) {
    return 0.0f;
}

bool UEndBattleAPI::BreakParts(AEndCharacter* ownerCharacter, FName uniqueName, bool forceDisableBattleLog, bool forceDisableDamageSource) {
    return false;
}

void UEndBattleAPI::BeginForceFieldMode(bool actorModeBattle, bool bDeactivateBattleCamera) {
}

void UEndBattleAPI::BeginBreak(AEndCharacter* Character, FName battleBreakID) {
}

void UEndBattleAPI::BeginBattleDirection(bool suspend) {
}

void UEndBattleAPI::AddStatusChangeID(AEndCharacter* Character, FName statusChangeID, EEndBattleStatusChangeTimeType timeType, bool ignoreResist, AEndCharacter* causeCharacter, bool Lock) {
}

void UEndBattleAPI::AddSpecialStatusChangeID(AEndCharacter* Character, AEndCharacter* causerCharacter, FName ID) {
}

void UEndBattleAPI::AddSpecialStateEffectWithBeamTarget(AEndCharacter* Character, FName specialStateEffectID, TArray<AEndCharacter*> beamTargetCharaList, bool bLineEffect, float LineEffectTangentLength) {
}

void UEndBattleAPI::AddSpecialStateEffect(AEndCharacter* Character, FName specialStateEffectID) {
}

void UEndBattleAPI::AddInvincibleThroughAbilityID(AEndCharacter* Character, FName AbilityId) {
}

void UEndBattleAPI::AddImpluse(AEndCharacter* Character, FVector Direction, float Magnitude) {
}

void UEndBattleAPI::AddIgnoreDamageSourceLookAtTraceActor(AEndCharacter* Character, AActor* IgnoreActor) {
}

void UEndBattleAPI::AddEnableTargetAbility(AEndCharacter* Character, FName AbilityId) {
}

void UEndBattleAPI::AddDangerSource(AEndCharacter* Instigator, float Duration, const TArray<FEndAIDangerInfo>& Infos, bool bResolveWithDamageSource) {
}

void UEndBattleAPI::AddCombinationGauge(AEndCharacter* Character, int32 Value) {
}

int32 UEndBattleAPI::AddBattleSceneCount(FName InName, int32 InAddCount) {
    return 0;
}

void UEndBattleAPI::AddBattleCameraRestrictedPlayOwners(TArray<AEndCharacterBase*> restrictedPlayOwners) {
}

void UEndBattleAPI::AddAttachEffect(AEndCharacter* Chara, FEndCharacterAttachEffectArguments args) {
}

void UEndBattleAPI::ActiveRagdoll(AEndCharacter* Character, bool bImmediately) {
}


