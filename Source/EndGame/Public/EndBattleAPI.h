#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EEndBattleAttributeType.h"
#include "EEndBattleSpecialStatusChangeType.h"
#include "EPlayerType.h"
#include "EndBattleCountAPI.h"
#include "EndDataObjectBattleAbilityAccessor.h"
#include "EndDataObjectBattleDamageSourceAccessor.h"
#include "AlphaBlend.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "EActorMoveMode.h"
#include "EEndAIBranchBit.h"
#include "EEndAISensorDangerObjectType.h"
#include "EEndAiBattleTargetType.h"
#include "EEndAiMathCmp.h"
#include "EEndAnimBehaviorMode.h"
#include "EEndBattleAITargetLockGroupPriority.h"
#include "EEndBattleBreakableRelationVolumeType.h"
#include "EEndBattleCharaCategoryType.h"
#include "EEndBattleCompareDistanceType.h"
#include "EEndBattleCompareLocationType.h"
#include "EEndBattleEnvironmentAnimPlayType.h"
#include "EEndBattleResidualParticlesEventType.h"
#include "EEndBattleSceneCountLifeCycleType.h"
#include "EEndBattleSpawnWeaponStateType.h"
#include "EEndBattleStatusChangeTimeType.h"
#include "EEndBattleSummonType.h"
#include "EEndBattleSupportFieldType.h"
#include "EEndBattleSyncActionEndType.h"
#include "EEndBattleUniqueAbilitySpawnWeaponType.h"
#include "EEndCharacterControllerStateType.h"
#include "EEndEnemyTerritorySituationType.h"
#include "EEndExtraActionLayer.h"
#include "EEndLocomotionAnimGroup.h"
#include "EEndLocomotionState.h"
#include "EEndPartsRepairConditionType.h"
#include "EModifierVolumeType.h"
#include "ETargetChoosingSort.h"
#include "ETargetChoosingTag.h"
#include "EWeaponSlot.h"
#include "EndAIDangerInfo.h"
#include "EndBattleMateriaParam.h"
#include "EndCharacterAttachEffectArguments.h"
#include "EndMenuJoin.h"
#include "GetOffsetTransform.h"
#include "EndBattleAPI.generated.h"

class AActor;
class AEndAIControllerBluePrintBase;
class AEndBattleSummonTargetPoint;
class AEndCharacter;
class AEndCharacterBase;
class AEndEnvironmentPhysicsStaticMeshActor;
class AEndNavModifierVolume;
class UAnimSequence;

UCLASS(Blueprintable)
class ENDGAME_API UEndBattleAPI : public UEndBattleCountAPI {
    GENERATED_BODY()
public:
    UEndBattleAPI();

    UFUNCTION(BlueprintCallable)
    static void ValidNearFadeEnvPhysicsActor();
    
    UFUNCTION(BlueprintCallable)
    static bool ValidateCombatAreaVolume(FName VolumeName, bool bValidate);
    
    UFUNCTION(BlueprintCallable)
    static void UpdateMoveGenjiShield(AEndCharacter* ownerCharacter, AEndCharacter* causerCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void UpdateAppearanceFrog(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool TryLayoutTransform(FName NodeName);
    
    UFUNCTION(BlueprintCallable)
    static bool TryGetCurrentFloorLocation(FVector& FloorLocation, AEndCharacterBase* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool SwitchMesh(AEndCharacter* Character, FName MeshName, FName MeshLabel);
    
    UFUNCTION(BlueprintCallable)
    static void SummonTrigger();
    
    UFUNCTION(BlueprintCallable)
    static void SummonPointManualSuspend(bool suspend);
    
    UFUNCTION(BlueprintCallable)
    static void SummonFinishingBlow();
    
    UFUNCTION(BlueprintCallable)
    static void SummonCutSceneAbilityException(FName excludeCharaSpecID, FName substituteCharaSpecID);
    
    UFUNCTION(BlueprintCallable)
    static void StopPartStartLoopEndMotion(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void StopPartLoopMotion(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void StopEnvironmentPhysFieldForce(FName GroupName);
    
    UFUNCTION(BlueprintCallable)
    static void StopEffect(int32 handleNumber);
    
    UFUNCTION(BlueprintCallable)
    static void StopCrowdActor(FName LevelName, FName AccessID, float BlendTime, bool bUseFade);
    
    UFUNCTION(BlueprintCallable)
    static void StopBattleCameraSequence(int32 sequenceActorUID);
    
    UFUNCTION(BlueprintCallable)
    static void StopAnimEnvironment(FName LevelName, FName AccessID);
    
    UFUNCTION(BlueprintCallable)
    static void StopAddMotion(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void StartEnvironmentPhysFieldForce(FName GroupName);
    
    UFUNCTION(BlueprintCallable)
    static bool StartBurst(AEndCharacter* Character, bool Force);
    
    UFUNCTION(BlueprintCallable)
    static bool SpawnWeaponCharacter(AEndCharacter* ownerCharacter, EEndBattleUniqueAbilitySpawnWeaponType weaponType, FName uniqueWeaponName, FName SpawnWeaponObjectName);
    
    UFUNCTION(BlueprintCallable)
    static AActor* SpawnSharedCharaSpec(AEndCharacterBase* Character, int32 Index);
    
    UFUNCTION(BlueprintCallable)
    static void SkipFadeCharaPopActor(FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static void ShowTargetAppearGUI(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ShowPhysics(FName ActorName, bool bSimulatePhysics);
    
    UFUNCTION(BlueprintCallable)
    static void SetWalkableFloorAngleOnBattleNav(AEndCharacter* InCharacter, float InWalkableAngle);
    
    UFUNCTION(BlueprintCallable)
    static void SetWalkableFloorAngle(AEndCharacter* InCharacter, float InWalkableAngle);
    
    UFUNCTION(BlueprintCallable)
    static void SetVisibilityWeapon(AEndCharacter* Character, bool bVisible, EWeaponSlot weaponSlotType, bool bSetToAnimationDefault, bool bAlsoSetToNeutral);
    
    UFUNCTION(BlueprintCallable)
    static void SetValidSmallSizeForSummonArea(bool Valid);
    
    UFUNCTION(BlueprintCallable)
    static void SetValidLargeSizeForSummonArea(bool Valid);
    
    UFUNCTION(BlueprintCallable)
    static void SetupChargeCrystal(AEndCharacter* ownerCharacter, FName uniqueName);
    
    UFUNCTION(BlueprintCallable)
    static void SetUnitParameter(AEndCharacter* Character, bool hideTargetList, bool disableTarget, bool disableTargetShowIcon, bool DisableDamageHit);
    
    UFUNCTION(BlueprintCallable)
    static void SetSummonInBossCutScene(bool bFlag);
    
    UFUNCTION(BlueprintCallable)
    static void SetSubCollisionPushBackSpeed(AEndCharacter* InChara, float InSpeed);
    
    UFUNCTION(BlueprintCallable)
    static void SetStoryFlagCondition(FName storyFlagNames, bool Condition);
    
    UFUNCTION(BlueprintCallable)
    static void SetSpecialStatusStateChangeID(AEndCharacter* Character, EEndBattleSpecialStatusChangeType Type, FName stateChangeID, FName paramID);
    
    UFUNCTION(BlueprintCallable)
    static void SetSpecialStatusChangeStateChangeID(AEndCharacter* Character, FName SpecialStatusChangeID, FName stateChangeID, TArray<float> Params, FName paramID, AActor* paramActor);
    
    UFUNCTION(BlueprintCallable)
    static void SetShowEnemyStatusGUI(AEndCharacter* Character, bool Show);
    
    UFUNCTION(BlueprintCallable)
    static void SetRootCapsuleAttackTargetSizeScale(AEndCharacter* Character, FVector AttackTargetSizeScale);
    
    UFUNCTION(BlueprintCallable)
    static void SetRigidBodyName(AEndCharacter* Character, FName RigidBodyName, bool bDeactivateOther);
    
    UFUNCTION(BlueprintCallable)
    static void SetRewardDelayEndBattle();
    
    UFUNCTION(BlueprintCallable)
    static void SetPrimaryAnimPack(AEndCharacter* Character, const FName InName, bool ignoreLowerPriority);
    
    UFUNCTION(BlueprintCallable)
    static void SetPerchSweepRadiusScale(AEndCharacter* InChara, float InScale);
    
    UFUNCTION(BlueprintCallable)
    static bool SetPartyLeader(EPlayerType Player, bool bIsInputTrigered);
    
    UFUNCTION(BlueprintCallable)
    static void SetPartsHPPercent(AEndCharacter* Character, FName BattleCharaPartsSpecID, float Percent);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverridePartsCameraLockSocketName(AEndCharacter* Character, FName BaseBattleCharaPartsSpecID, FName SocketName, float BlendTime, EAlphaBlendOption BlendOption);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideMovementBaseByComponentTags(AEndCharacter* InCharacter, AActor* InMovementBaseActor, FName ComponentTag);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideLocomotionAnimSequenceName(AEndCharacter* InChara, EEndLocomotionAnimGroup AnimGroup, FName AnimSequenceName, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideKeepFromAbility(AEndCharacter* Character, FName InAbilityName);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideKeep(AEndCharacter* Character, int32 InKeep);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideEnemyBookID(AEndCharacter* Character, FName EnemyBookID);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideCapsuleSize(AEndCharacter* InCharacter, float InRadius, float InCapsuleHalfHeight);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideCameraLockSocketName(AEndCharacter* Character, FName SocketName, float BlendTime, EAlphaBlendOption BlendOption);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideBattleDefenseID(AEndCharacter* Character, FName battleDefenseID);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideBattleCharaSpec(AEndCharacter* Character, FName BattleCharaSpecID);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideBattleCharaPartsSpec(AEndCharacter* Character, FName BaseID, FName OverrideId, bool bChangeHP);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideAdditiveDamage(AEndCharacter* InChara, FName AnimSequenceName);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideActiveAimAngle(AEndCharacter* Character, FVector2D ActiveYawRange, FVector2D ActivePitchRange);
    
    UFUNCTION(BlueprintCallable)
    static void SetOverrideAbilityKeep(AEndCharacter* Character, int32 Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetMovementSplineConstraint(AEndCharacterBase* InCharacter, AActor* InSplineActor, FName ComponentTag);
    
    UFUNCTION(BlueprintCallable)
    static void SetLockHeat(AEndCharacter* Character, bool Locked);
    
    UFUNCTION(BlueprintCallable)
    static void SetInvalidPerchRadiusScale(AEndCharacter* InChara, float InScale);
    
    UFUNCTION(BlueprintCallable)
    static void SetImmotality(AEndCharacter* InChara, bool InImmotality);
    
    UFUNCTION(BlueprintCallable)
    static bool SetIgnoreSummonTargetPointFromActorName(FName InActorName, bool ignore);
    
    UFUNCTION(BlueprintCallable)
    static void SetIgnorePushActorsByAccessID(AEndCharacter* Character, bool bIgnore, const TArray<FName>& AccessIDs);
    
    UFUNCTION(BlueprintCallable)
    static void SetIgnorePushActors(AEndCharacter* Character, bool bIgnore, const TArray<FName>& LevelNames, const TArray<FName>& ActorNames);
    
    UFUNCTION(BlueprintCallable)
    static void SetIgnoreMoveOnlyNavMesh(AEndCharacter* Character, bool bIgnoreMoveOnlyNavMesh);
    
    UFUNCTION(BlueprintCallable)
    static void SetIgnoreDisperseTarget(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void SetHPPercent(AEndCharacter* Character, int32 Percent);
    
    UFUNCTION(BlueprintCallable)
    static void SetHitCharaResponse(AEndCharacterBase* Character, bool bHitChara);
    
    UFUNCTION(BlueprintCallable)
    static void SetHideTargetList(AEndCharacter* Character, bool hide);
    
    UFUNCTION(BlueprintCallable)
    static void SetHideSummonWithSkillCamera(bool enableHide);
    
    UFUNCTION(BlueprintCallable)
    static void SetHide(AEndCharacter* Character, bool hide);
    
    UFUNCTION(BlueprintCallable)
    static void SetHiddenVolumeRelatedBreakable(EEndBattleBreakableRelationVolumeType VolumeType, bool bHidden, const TArray<FName>& BreakableIDs);
    
    UFUNCTION(BlueprintCallable)
    static void SetHiddenBreakablesTwoParam(bool bHidden, const TArray<FName>& AccessIDs);
    
    UFUNCTION(BlueprintCallable)
    static void SetHiddenBreakables(bool bHidden, const TArray<FName>& LevelNames, const TArray<FName>& AccessIDs);
    
    UFUNCTION(BlueprintCallable)
    static void SetHiddenBreakable(bool bHidden, FName LevelName, FName AccessID);
    
    UFUNCTION(BlueprintCallable)
    static void SetHeat(AEndCharacter* Character, bool Enable, float Duration);
    
    UFUNCTION(BlueprintCallable)
    static void SetForcedLODMode(AEndCharacter* Character, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetForceActionRestriction(AEndCharacter* Character, bool forceActionRestriction);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableSlip(AEndCharacter* Character, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableSleepAnimationAttachCharacterOnly(AEndCharacter* Character, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableResidentBlend(AEndCharacter* Character, FName ResidentBlendName, bool bEnabled, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableRegeneOfCharaParts(AEndCharacter* InCharacter, FName InPartsID, bool InEnable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnablePushCollision(AEndCharacter* Character, FName partId, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableEquipmentSkillFrogAlways(bool Enable, bool frogAfterDebuffDisable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnabledUpdateAimLocation(AEndCharacter* Character, bool bEnabled);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableControlDamageToParts(AEndCharacter* InCharacter, bool InDamageToOnePart);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBreakPartsDamage(AEndCharacter* Character, FName BattleCharaPartsSpecID, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBreakDamage(AEndCharacter* Character, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBreakable(FName LevelName, FName AccessID, bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBonamikGroup(AEndCharacter* Character, FName BonamikGroupName, bool bEnabled, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBonamikGroundCollision(AEndCharacter* Character, FName BonamikGroupName, bool bEnabled);
    
    UFUNCTION(BlueprintCallable)
    static void SetEnableBattleAway(bool Enable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDyingAbilityID(AEndCharacter* Character, FName AbilityId);
    
    UFUNCTION(BlueprintCallable)
    static void SetDuringCommandAbilityInvalidPeriod(AEndCharacter* targetPlayerCharacter, bool bInvalid);
    
    UFUNCTION(BlueprintCallable)
    static void SetDrawPauseEnvironmentPhysicsActors(TArray<AActor*> objectList, bool drawPause, bool tickPause);
    
    UFUNCTION(BlueprintCallable)
    static void SetDrawPauseEnvironment(FName LevelName, FName AccessID, bool bPause, bool bIncludingCollision);
    
    UFUNCTION(BlueprintCallable)
    static void SetDrawPauseCharacter(AEndCharacter* Character, bool bPause);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisperseTarget(AEndCharacter* Executor, AEndCharacter* TargetPlayer);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableTargetOfParts(AEndCharacter* Character, FName BattleCharaPartsSpecID, bool bDisableTarget);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableTargetNew(AEndCharacter* Character, bool Disable, bool showIcon);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableTarget(AEndCharacter* InChara, bool InDisable, bool hitDamage, bool refreshTargetLock);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableSummoning(bool Enable, int32 PhaseNumber);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableSubCollisionByGroupName(AEndCharacter* InChara, FName InGroupName, bool bDisable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableSubCollision(AEndCharacter* InChara, bool bDisable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableStealTextLabel(const FString& TextLabel);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableSteal(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableReserveMemberCommand(bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableReactionAndBreak(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableReaction(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisablePartsBreak(AEndCharacter* Character, bool bDisable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableParts(AEndCharacter* Character, FName BattleCharaPartsSpecID, bool bDisableTarget, bool bDisableDamage, bool bDisableDamageCollision);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableGameOver(bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableFinish(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableDeadDestroy(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableDamageHit(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableBurst(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableBodyHPDecrementByParts(AEndCharacter* Character, bool bDisable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableBodyDamagePopupByParts(AEndCharacter* Character, bool bDisable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDisableActionRestriction(AEndCharacter* Character, bool Disable);
    
    UFUNCTION(BlueprintCallable)
    static void SetDamageHitResponse(AEndCharacterBase* Character, bool bHitDamage);
    
    UFUNCTION(BlueprintCallable)
    static void SetCollisionEnableByComponentTag(AActor* InActor, bool bEnable, FName ComponentTag);
    
    UFUNCTION(BlueprintCallable)
    static void SetCharacterMovementMode(AEndCharacter* InChara, bool bMovable, bool bHitWall, bool bHitObject, bool bFitFloor, bool bMaxWeight);
    
    UFUNCTION(BlueprintCallable)
    static void SetCharacterBehaviorParts(AEndCharacter* Character, AEndCharacter* parentCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void SetCharacterBehaviorMode(AEndCharacter* Character, EEndAnimBehaviorMode Mode, bool immediate);
    
    UFUNCTION(BlueprintCallable)
    static void SetBurstForceAerial(AEndCharacter* InChara, bool Flag);
    
    UFUNCTION(BlueprintCallable)
    static void SetBreakPartsDamageID(AEndCharacter* Character, FName BattleCharaPartsSpecID, FName BreakID);
    
    UFUNCTION(BlueprintCallable)
    static void SetBreakPartsDamage(AEndCharacter* Character, FName BattleCharaPartsSpecID, FName BreakID, float breakDamageHPMaxPercent);
    
    UFUNCTION(BlueprintCallable)
    static void SetBreakDamage(AEndCharacter* Character, FName BreakID, float breakDamageHPMaxPercent);
    
    UFUNCTION(BlueprintCallable)
    static void SetBPPercent(AEndCharacter* Character, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetBPDamageCoefficient(AEndCharacter* Character, float Coefficient);
    
    UFUNCTION(BlueprintCallable)
    static void SetBP(AEndCharacter* Character, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleSceneCountLifeCycle(FName InName, EEndBattleSceneCountLifeCycleType InType, int32 InValue);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleSceneCount(FName InName, int32 InCount);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleSafeTransform(AEndCharacter* InChara, bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleAbilityRotateStatePointName(AEndCharacter* Character, FName PointName);
    
    UFUNCTION(BlueprintCallable)
    static void SetBattleAbilityRotateStateLocation(AEndCharacter* Character, const FVector& Location);
    
    UFUNCTION(BlueprintCallable)
    static void SetATBAll(float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetATB(EPlayerType PlayerType, float Value);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCToSafeArea(EPlayerType PlayerCharacter, int32 GroupId, bool Flag, bool bIncludeReserve, bool bFollowUCPC, FVector AvoidLocation);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCTargetDirect(const EPlayerType PlayerCharacter, AEndCharacter* TargetCharacter, TArray<FName> PartsIDList);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCTargetChoosingParam(EPlayerType PlayerCharacter, TArray<ETargetChoosingTag> PriorityTagList, ETargetChoosingSort SortMethod, TArray<AEndCharacter*> AssignedTargets);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCIgnoreHeight(EPlayerType PlayerType, bool InFlag);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCExcludeTarget(EPlayerType PlayerType, AEndCharacter* TargetCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCExcludeArea(const EPlayerType PlayerCharacter, int32 GroupId, const bool Flag, bool bIncludeReserve);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCDisconnectArea(const AEndCharacter* InCharacter, int32 InGroupId);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCConfrontIdle(EPlayerType InPlayerType, bool InFlag, bool bIncludeReserve);
    
    UFUNCTION(BlueprintCallable)
    static void SetAIPCCombatArea(const EPlayerType PlayerCharacter, int32 GroupId, const bool Flag, bool bIncludeReserve);
    
    UFUNCTION(BlueprintCallable)
    static void SetAimTargetOffsetHeight(AEndCharacter* Character, float OffsetHeight);
    
    UFUNCTION(BlueprintCallable)
    static void SetActorPause(AActor* Actor, bool bTickPause, bool bDrawPause);
    
    UFUNCTION(BlueprintCallable)
    static void SetActorMoveMode(AEndCharacter* Character, EActorMoveMode actorMoveMode);
    
    UFUNCTION(BlueprintCallable)
    static void SetActorLocationToRoot(AEndCharacter* Character, FVector NewLocation);
    
    UFUNCTION(BlueprintCallable)
    static void SetActorLocationAndRotationToRoot(AEndCharacter* Character, FVector NewLocation, FRotator NewRotator);
    
    UFUNCTION(BlueprintCallable)
    static void SendSystemMessage(const FString& InMessage);
    
    UFUNCTION(BlueprintCallable)
    static void SendPhaseNumberToSummonSystem(int32 currentPhase);
    
    UFUNCTION(BlueprintCallable)
    static void SendMetaMessage(const FString& InMessage);
    
    UFUNCTION(BlueprintCallable)
    static bool SendGenjiShieldToPlayBattleCamera(AEndCharacter* ownerCharacter, int32 sequenceActorUID);
    
    UFUNCTION(BlueprintCallable)
    static void SendEventResidualParticles(AEndCharacter* ownerCharacter, EEndBattleResidualParticlesEventType EventType, bool otherThanOwner);
    
    UFUNCTION(BlueprintCallable)
    static void SendEventDamageSourceTheTableNumber(AEndCharacter* Character, FName DamageSourceID, int32 tableNumber);
    
    UFUNCTION(BlueprintCallable)
    static void SendEventDamageSource(AEndCharacter* Character, FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    static void RestrictBattleFieldBySummonBoss();
    
    UFUNCTION(BlueprintCallable)
    static void ResetWalkableFloorAngleOnBattleNav(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ResetWalkableFloorAngle(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ResetUniqueAbilityDerivedFixedAbilityID(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetSummonPointToIncreaseOneSecond();
    
    UFUNCTION(BlueprintCallable)
    static void ResetSummonCutSceneReturnLocation(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetSummonCondition();
    
    UFUNCTION(BlueprintCallable)
    static void ResetSubCollisionPushBackSpeed(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static void ResetRootCapsuleAttackTargetSizeScale(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetRigidBodyName(AEndCharacter* Character, FName RigidBodyName);
    
    UFUNCTION(BlueprintCallable)
    static void ResetPrimaryAnimPack(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverridePartsCameraLockSocketName(AEndCharacter* Character, FName BaseBattleCharaPartsSpecID, float BlendTime, EAlphaBlendOption BlendOption);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideMovementBase(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideLocomotionAnimSequenceName(AEndCharacter* InChara, EEndLocomotionAnimGroup AnimGroup, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideKeep(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideEnemyBookID(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideCapsuleSize(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideCameraLockSocketName(AEndCharacter* Character, float BlendTime, EAlphaBlendOption BlendOption);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideBattleDefenseID(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideBattleCharaSpec(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideBattleCharaPartsSpec(AEndCharacter* Character, FName BaseID);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideAdditiveDamage(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static void ResetOverrideActiveAimAngle(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetHitCharaResponse(AEndCharacterBase* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetDisperseTarget();
    
    UFUNCTION(BlueprintCallable)
    static void ResetDisableStealTextLabel();
    
    UFUNCTION(BlueprintCallable)
    static void ResetDamageHitResponse(AEndCharacterBase* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetCharacterMovementMode(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static void ResetBreakWeakAttributeDamageValue(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetBreakPartsDamageValue(AEndCharacter* Character, FName BattleCharaPartsSpecID);
    
    UFUNCTION(BlueprintCallable)
    static void ResetBreakDamageValue(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetBP(AEndCharacter* Character, bool bResetAnimation);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAppearanceFrog(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAppearance(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAIPCTargetDirect(const EPlayerType PlayerCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAIPCTargetChoosingParam(const EPlayerType PlayerCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAIPCExcludeTarget(EPlayerType PlayerType);
    
    UFUNCTION(BlueprintCallable)
    static void ResetAIPCDisconnectArea();
    
    UFUNCTION(BlueprintCallable)
    static void ResetAimTargetOffsetHeight(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestUniqueAbilitySpawnWeapon(AEndCharacter* ownerCharacter, EEndBattleUniqueAbilitySpawnWeaponType weaponType, EEndBattleSpawnWeaponStateType weaponStateType, FName uniqueWeaponName);
    
    UFUNCTION(BlueprintCallable)
    static void RequestSyncActionEnd(AEndCharacter* Chara, EEndBattleSyncActionEndType Type, AEndCharacter* causerCharacter);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestSummonEnemyPreloadCutSceneAbility(AEndCharacter* InCharacter, FName InCutSceneID, FName InDamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestSummonEnemyPlayCutSceneAbility(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestSummonEnemyCutSceneAbility(AEndCharacter* InCharacter, FName InCutSceneID, FName InDamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    static void RequestShowAbilityName(AEndCharacter* Character, const FString& String, float InTime, bool bNonGuardableIcon);
    
    UFUNCTION(BlueprintCallable)
    static void RequestReturnSummon();
    
    UFUNCTION(BlueprintCallable)
    static void RequestPreloadCutScene(FName CutSceneID);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestCurrentChargeCrystalDisappears(AEndCharacter* ownerCharacter);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestCreateDestructionParts(AEndCharacter* ownerCharacter, FName uniqueName, FName spawnCharaSpecName, FName partsAttachSocketName, bool recreate);
    
    UFUNCTION(BlueprintCallable)
    static bool RequestBrokenDestructionParts(AEndCharacter* ownerCharacter, FName uniqueName);
    
    UFUNCTION(BlueprintCallable)
    static void RequestAttachSyncAction(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void RepairParts(AEndCharacter* Character, FName BattleCharaPartsSpecID, FName MeshLabel, EEndPartsRepairConditionType Condition);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveStatusChangeID(AEndCharacter* Character, FName statusChangeID, bool Lock);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveSpecialStatusChangeType(AEndCharacter* InChara, EEndBattleSpecialStatusChangeType InType);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveSpecialStatusChangeIDRequest(AEndCharacter* Character, FName ID);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveSpecialStatusChangeID(AEndCharacter* Character, FName ID);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveSpecialStateEffect(AEndCharacter* Character, FName specialStateEffectID);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveIgnoreDamageSourceLookAtTraceActor(AEndCharacter* Character, AActor* IgnoreActor);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveDangerSource(AEndCharacter* Instigator, EEndAISensorDangerObjectType Type);
    
    UFUNCTION(BlueprintCallable)
    static void RemoveAttachEffect(AEndCharacter* Chara, const FName AttachSocketName, const FName ResourceName, bool bDestroy);
    
    UFUNCTION(BlueprintCallable)
    static void ReleaseBattleFieldBySummonBoss();
    
    UFUNCTION(BlueprintCallable)
    static void ReGuard(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool RegisterTargetLockGroup(AEndCharacter* Character, const TArray<AEndCharacter*>& TargetList, int32 MaxEachTargetNum, bool bPrioritizeUCPC, FName GroupName, EEndBattleAITargetLockGroupPriority Priority, bool bIgnoreProvocation, bool bNoLockLastOne);
    
    UFUNCTION(BlueprintCallable)
    static void RaycastWallFromChara(AEndCharacter* InCharacter, float InOffsetYaw, float InCastRange, bool& OutHit, float& OutDistance, FHitResult& OutParam);
    
    UFUNCTION(BlueprintCallable)
    static bool RaycastTerrainFromChara(FHitResult& HitResult, AEndCharacter* Character, FName SocketName, FVector Offset, TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
    
    UFUNCTION(BlueprintCallable)
    static void RaycastSphereWallFromChara(AEndCharacter* InCharacter, float InOffsetYaw, float InCastRange, float InRadius, bool& OutHit, float& OutDistance, FHitResult& OutParam);
    
    UFUNCTION(BlueprintCallable)
    static void PlayPartStartLoopEndMotion(AEndCharacter* Character, FName StartMotionName, FName LoopMotionName, FName endMotionName, FName BoneName, EEndExtraActionLayer Layer, float LoopTime);
    
    UFUNCTION(BlueprintCallable)
    static void PlayPartMotion(AEndCharacter* Character, FName MotionName, FName BoneName, EEndExtraActionLayer Layer, float overrideBlendIn, float overrideBlendOut);
    
    UFUNCTION(BlueprintCallable)
    static void PlayPartLoopMotion(AEndCharacter* Character, FName MotionName, FName BoneName, EEndExtraActionLayer Layer);
    
    UFUNCTION(BlueprintCallable)
    static void PlayInterruptAnimInBurst(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static int32 PlayEffectFromResourceCharacter(int32 CategoryType, AActor* ResourceActor, FName ResourceName, AActor* AttachActor, FName AttachSocketName, bool NotSynchronizeInvisible);
    
    UFUNCTION(BlueprintCallable)
    static int32 PlayEffect(int32 CategoryType, FName ResourceName, AActor* AttachActor, FName AttachSocketName, bool NotSynchronizeInvisible);
    
    UFUNCTION(BlueprintCallable)
    static bool PlayDitherFadeEffect(int32 CategoryType, FName ResourceName, AEndCharacter* ownerCharacter, FName AttachSocketName);
    
    UFUNCTION(BlueprintCallable)
    static void PlayCrowdActor(FName LevelName, FName AccessID, float BlendTime, bool bUseFade);
    
    UFUNCTION(BlueprintCallable)
    static int32 PlayBattleCameraSequenceSpecialSkill(FName CameraSequenceID, AEndCharacterBase* OwnerChara, AEndCharacterBase* HasResourceChara, AActor* TargetActor);
    
    UFUNCTION(BlueprintCallable)
    static int32 PlayBattleCameraSequence(FName CameraSequenceID, AEndCharacterBase* OwnerChara, AEndCharacterBase* HasResourceChara, AActor* TargetActor, bool bIsToRegisterSlaveViewOnly, float MassiveEnvironmentFrustrumScaleForMainPass);
    
    UFUNCTION(BlueprintCallable)
    static void PlayAnimEnvironmentBeginLoop(FName LevelName, FName AccessID, FName BeginAnimName, FName LoopAnimName);
    
    UFUNCTION(BlueprintCallable)
    static void PlayAnimEnvironment(FName LevelName, FName AccessID, FName AnimName, EEndBattleEnvironmentAnimPlayType PlayType);
    
    UFUNCTION(BlueprintCallable)
    static void PlayAddMotion(AEndCharacter* Character, FName MotionName, EEndExtraActionLayer Layer, bool bInfiniteLoop);
    
    UFUNCTION(BlueprintCallable)
    static void OverrideSummonPointToIncreaseOneSecond(float Point);
    
    UFUNCTION(BlueprintCallable)
    static void OverrideSummonCutSceneReturnLocation(AEndCharacter* Character, FTransform Transform);
    
    UFUNCTION(BlueprintCallable)
    static void OverrideSummonCaptureTimeLimit(float Time);
    
    UFUNCTION(BlueprintCallable)
    static void OverrideDamageSourceIDCutSceneAbility(AEndCharacter* InCharacter, FName InDamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    static void OnSummonFinishActivatePhase();
    
    UFUNCTION(BlueprintCallable)
    static void OnSummonActivateTriggerAction();
    
    UFUNCTION(BlueprintCallable)
    static void NotifyAbilityReaction(AEndCharacter* Character, float Param0);
    
    UFUNCTION(BlueprintCallable)
    static bool NavmeshRaycastFromChara(AEndCharacter* InCharacter, float InOffsetYaw, float& OutDistance, float InCastRange, bool InForceSSizeNav, bool InDrawDebug, float InDrawDebugTime, bool NoCheckEscapeWall);
    
    UFUNCTION(BlueprintCallable)
    static bool NavmeshRaycast(FVector InLocation, FVector InDirection, float& OutDistance, AEndCharacterBase* InExecutor, float InCastRange, bool InDrawDebug, float InDrawDebugTime, bool NoCheckEscapeWall);
    
    UFUNCTION(BlueprintCallable)
    static void MoveGenjiShield(AEndCharacter* ownerCharacter, AEndCharacter* causerCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsUniqueAbility(FName AbilityId);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsUCPC(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool IsSummonGaugeZero();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsSummon(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsSetRigidBodyName(AEndCharacter* Character, FName RigidBodyName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsRideFatMoogle(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool IsPlayingBattleCameraSequence(int32 sequenceActorUID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsPlayingAnimEnvironment(FName LevelName, FName AccessID, FName AnimName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsPlayerCharacterValid(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsPlayer(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsOverlapPoint(AEndNavModifierVolume* InVolume, FVector InPoint);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsOverlapCharaFromName(FName InVolumeName, AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsNormal(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsMagic(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsLimit(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsLaunchActionPlaying(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsLaunchActionInAir(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsItem(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInSyncAction(AEndCharacter* Chara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInSupportField(AEndCharacter* Character, EEndBattleSupportFieldType supportFieldType);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInSummonCutScene();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInScreen(AActor* Actor);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInFanRange(AEndCharacter* ownerCharacter, float baseYaw, float angleRange, float radiusMin, float radiusMax, FVector targetPosition);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInEnemySummonCutScene();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsInBattle();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsHPPercent(AEndCharacter* InChara, int32 Percent, EEndAiMathCmp Cmp);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsGuard(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsFillLimitPlayer(FName PlayerCharaName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDummyPartyMember(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDodgeResetUniqueAbility(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static bool IsDisperseTargetExecutor(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDisableTarget(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintPure)
    static bool IsDamageSourceFlagDisableFinish(int64 Flag);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDamage(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsContainedMotionListArray(AEndCharacter* InChara, const TArray<FName>& InMot);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsContainedMotionList5(AEndCharacter* InChara, FName InMot1, FName InMot2, FName InMot3, FName InMot4, FName InMot5);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsContainedMotionList4(AEndCharacter* InChara, FName InMot1, FName InMot2, FName InMot3, FName InMot4);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsContainedMotionList3(AEndCharacter* InChara, FName InMot1, FName InMot2, FName InMot3);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsContainedMotionList2(AEndCharacter* InChara, FName InMot1, FName InMot2);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsContainedMotionList(AEndCharacter* InChara, FName InMot1);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCommandAbilityCombination(AEndCharacter* Character);
    
    UFUNCTION(BlueprintPure)
    static bool IsCombinationAbilityFromDataObjectBattleAbility(int64 Flag0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCloudOffensiveMode();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCharaID(AEndCharacter* InChara, const FName Upper, const FName Lower);
    
    UFUNCTION(BlueprintCallable)
    static void IsCharacterValidBranch(AEndCharacter* InCharacter, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCharacterValid(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsBurst(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsBrokenParts(AEndCharacter* Character, FName BattleCharaPartsSpecID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsBreakEndAction(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsBreak(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool IsAIPCRangedWeaponEquipped(const EPlayerType PlayerCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsAIPC(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsAdditiveDamagePlaying(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsActionRestriction(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsAbility(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable)
    static void InvalidNearFadeEnvPhysicsActor();
    
    UFUNCTION(BlueprintCallable)
    static int32 IncBattleSceneCount(FName InName);
    
    UFUNCTION(BlueprintCallable)
    static void HidePhysics(FName ActorName);
    
    UFUNCTION(BlueprintCallable)
    static void HideAbilityName(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool HasStatusChangeID(AEndCharacter* Character, FName statusChangeID);
    
    UFUNCTION(BlueprintCallable)
    static bool HasSpecialStatusChangeType(AEndCharacter* InChara, EEndBattleSpecialStatusChangeType InType);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool HasSpecialStatusChangeID(AEndCharacter* Character, FName ID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool HasDamageSource(AEndCharacter* InChara, FName InDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool HasAbilityElement(FName InAbilityName, EEndBattleAttributeType InType);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetWorldLocationAngle(const FVector& BaseLocation, const FVector& TargetLocation);
    
    UFUNCTION(BlueprintCallable)
    static void GetTrophyFirstRescue();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTargetLocationAngle(AEndCharacter* Character, FVector TargetLocation);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetTargetCharacterAngle(AEndCharacter* Character, AEndCharacter* TargetCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetTargetCharacter(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSyncActionIDLast(AEndCharacter* Chara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetSyncActionID(AEndCharacter* Chara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndBattleSummonTargetPoint* GetSummonTargetPointFromActorName(FName InActorName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetSummonAvilableTime();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetSummom(EEndBattleSummonType Type);
    
    UFUNCTION(BlueprintCallable)
    static float GetSubCollisionPushBackSpeed(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetStoryFlagConditionNum(TArray<FName> storyFlagNames, bool Condition, int32 initializeNum);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetSpendATBBarTotal(AEndCharacter* EndCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetSpecialStatusChangeType(AEndCharacter* Character, TArray<EEndBattleSpecialStatusChangeType>& typeList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetSpecialStatusChangeParamFloat(AEndCharacter* Character, EEndBattleSpecialStatusChangeType Type, FName paramID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetSocketTransform(AEndCharacter* InChara, FName InSocketName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetRiddenMasterCharacter(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetResistanceElement(AEndCharacter* InChara, int32 InType);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetReplaceDamageSourceID(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetRaceName(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetPlayingExtraActionSequenceNames(TArray<FName>& OutNames, AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static EPlayerType GetPlayerType(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetPlayerCharacter(EPlayerType Type);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AActor*> GetPhysicsInVolumeFromLocation(FName InVolumeName, FName LocationName, FName InName, bool InContain, bool InPossetion, bool InCanPosettion);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AActor*> GetPhysicsInVolume(FName InVolumeName, FName InName, bool InContain, bool InPossetion);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndEnvironmentPhysicsStaticMeshActor*> GetPhysicsFromLocation(FName LocationName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AActor*> GetPhysicsFromActorName(FName InName, bool InContain);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPhysicsDefense(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPhysicsAttack(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AActor*> GetPhysics(FName InName, bool InContain);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetPartyMembersIgnoreDead();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetPartyLeader();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetPartsHPPercent(AEndCharacter* Character, FName BattleCharaPartsSpecID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndNavModifierVolume*> GetOverlapVolumes(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetOffsetTransform(const FTransform& Transform, const FVector& Offset, TEnumAsByte<GetOffsetTransform::Type> RotationType);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetNearestTargetPointName(FVector BaseLocation, TArray<FName> targetPointNameList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetNearestSocketName(FVector BaseLocation, TArray<FName> SocketNameList, AEndCharacter* HasSocketNameChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetNearestRangePartyCharacter(AEndCharacter* InChara, float Range, bool ZVisible);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AActor* GetNearestPhysicsInVolumeFromLocation(AEndCharacter* InChara, FName InVolumeName, FName LocationName, FName InName, bool InContain, bool InPossetion, bool InCanPosettion);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AActor* GetNearestPhysicsInVolume(AEndCharacter* InChara, FName InVolumeName, FName InName, bool InContain, bool InPossetion);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AActor* GetNearestPhysicsFromActorName(AEndCharacter* InChara, FName InName, bool InContain);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AActor* GetNearestPhysics(AEndCharacter* InChara, FName InName, bool InContain);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetNearestOwnVolumeWithExtent(AEndCharacter* InChara, FVector InLocation, FVector InExtent);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetNearestOwnVolume(AEndCharacter* InChara, FVector InLocation);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetNearestCharacter(FVector InLocation, TArray<AEndCharacter*> InList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetNearestActor(AActor*& outActor, AActor* baseActor, const TArray<AActor*>& compareActorList, const TArray<AActor*>& ignoreActorList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndNavModifierVolume*> GetNavVolumeFromType(FName InBattleSceneID, TEnumAsByte<EModifierVolumeType::Type> InType);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndNavModifierVolume* GetNavVolumeFromAngle(AEndCharacter* InChara, float InAngleRange, EEndBattleCompareDistanceType InType, int32 InGroup, bool InBehind);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<FName> GetMotionList(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool GetMateriaParam(AEndCharacter* InChara, bool bWeapon, int32 Slot, FEndBattleMateriaParam& Param);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicDefense(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetMagicAttack(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static FTransform GetLayoutTransform(FName NodeName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetKeep(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHPPercent(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetHPMax(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static EEndBattleCharaCategoryType GetHighestPriorityBattleCharaCategory(const FName& territoryID);
    
    UFUNCTION(BlueprintCallable)
    static bool GetHiddenBreakable(FName LevelName, FName AccessID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetGuardTime(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool GetFirstDamageTime(float& FirstDamageTime, const UAnimSequence* AnimSequecne, float StartTime);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AActor* GetFarestPhysics(AEndCharacter* InChara, float InRadius, FName InName, bool InContain);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetFarestCharacter(FVector InLocation, TArray<AEndCharacter*> InList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetFarestActor(AActor*& outActor, AActor* baseActor, const TArray<AActor*>& compareActorList, const TArray<AActor*>& ignoreActorList);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetExpectationCountInConeAreaByLocation(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float ConeRadius, float ConeAngle, FVector TargetLocation, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetExpectationCountInConeArea(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float ConeRadius, float ConeAngle, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetExpectationCountInCapsuleAreaByLocation(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float CapsuleRadius, float CapsuleLength, FVector TargetLocation, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetExpectationCountInCapsuleArea(AEndCharacter* InCharacter, TEnumAsByte<EEndAiBattleTargetType::Type> TargetType, float CapsuleRadius, float CapsuleLength, float FowardVectorRotateAngle, bool InDrawDebug, float InDrawDebugTime);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetEnvironmentSocketTransform(FName LevelName, FName AccessID, FName SocketName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static EEndEnemyTerritorySituationType GetEnemyTerritorySituationType(const FName& territoryID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetEnemyMembersRef(TArray<AEndCharacter*>& Out);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetEnemyMembersFromID(FName Upper, FName Lower, bool Flip);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetEnemyMemberFromIDWithIndex(FName Upper, FName Lower, int32 InIndex);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetEnemyMemberCountFromID(FName Upper, FName Lower, bool Flip);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetEnemyMemberCount(FName ContainRaceID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<FName> GetEncountBattleSceneIDs();
    
    UFUNCTION(BlueprintCallable)
    static bool GetEnableBreakable(FName LevelName, FName AccessID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetDummyPartyMembers();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetDummyNPCsFromID(FName Upper, FName Lower);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<AEndCharacter*> GetDummyEnemies();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool GetDataObjectBattleDamageSourceFromAbilityID(FName AbilityId, FEndDataObjectBattleDamageSourceAccessor& dataObjectBattleDamageSource);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool GetDataObjectBattleDamageSource(FName DamageSourceID, FEndDataObjectBattleDamageSourceAccessor& dataObjectBattleDamageSource);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool GetDataObjectBattleAbility(FName AbilityId, FEndDataObjectBattleAbilityAccessor& dataObjectBattleAbility);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<FVector> GetDamageSourceLocations(TArray<FName> DamageSourceIDs, AEndCharacter* ownerCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDamageSourceCountInArea(FName InDamageSourceID, AActor* ActorToSearchAround, float SearchRadius, bool bFlatSearch);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetDamageSourceCount(FName InDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static uint8 GetDamageHitReactionTableIndex(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static EEndLocomotionState GetCurrentLocomotionState(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCurrentAbilityID(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetCompareLocation(FVector BaseLocation, const TArray<FVector>& compareLocationList, bool bCompare2D, EEndBattleCompareLocationType compareType);
    
    UFUNCTION(BlueprintCallable)
    static FName GetCombinationAbilityUsedCharacterName(FName AbilityId);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCharaSpecName(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetCharaID(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCharaHP(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetCharaFromRaceID(FName InRaceName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndCharacter* GetCharaFromActorName(FName InActorName, bool bAllowFindCharaPopManager);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static EEndCharacterControllerStateType GetCharacterStateType(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetCharactersFromID(FName Upper, FName Lower, TArray<AEndCharacter*>& OutList, TArray<AEndCharacter*> InList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetCharacterNameSymbolIndex(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBreakTime(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBPPercent(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetBP(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetBattleSceneIDFromChara(AEndCharacter* InChara, bool InParent);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBattleSceneCount(FName InName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetBattleMemberConditionList(bool dead, bool sleep, bool Stop, bool petrify, bool Toad, TArray<AEndCharacter*>& MemberList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetBattleCharaSpec_DataTableID(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable)
    static FName GetBattleCameraSequenceID(int32 sequenceActorUID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static void GetAttackableCharacters(TArray<AEndCharacter*>& OutList, TArray<AEndCharacter*> InList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static TArray<FVector> GetAllDamageSourceLocations(FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static AEndAIControllerBluePrintBase* GetAIController(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FName GetActorName(AEndCharacter* InChara);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static float GetActorDistance(AActor* From, AActor* To);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetActorDirection(AActor* From, AActor* To);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static int32 GetAbilityElement(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable)
    static void GameOverForce();
    
    UFUNCTION(BlueprintCallable)
    static void ForceDisableAimEffectorSetting(AEndCharacter* Character, FName EffectorSettingName);
    
    UFUNCTION(BlueprintCallable)
    static void ForceDestroyParts(AEndCharacter* ownerCharacter, FName uniqueName);
    
    UFUNCTION(BlueprintCallable)
    static void FinishSummonOmenEffect();
    
    UFUNCTION(BlueprintCallable)
    static TArray<AEndNavModifierVolume*> FindNavVolumesOutRange(AEndCharacter* Character, TArray<int32> Groups, float angleRange, EEndBattleCompareDistanceType Type, bool behind, float Distance);
    
    UFUNCTION(BlueprintCallable)
    static TArray<AEndNavModifierVolume*> FindNavVolumesInRange(AEndCharacter* Character, TArray<int32> Groups, float angleRange, EEndBattleCompareDistanceType Type, bool behind, float Distance);
    
    UFUNCTION(BlueprintCallable)
    static bool FindEnableCrystalAppearPoint(AEndCharacter* ownerCharacter, float nearLength, float farLength, float viewAngle, FName& outPointName, FTransform& outPointTransform);
    
    UFUNCTION(BlueprintCallable)
    static bool ExistsNavmeshWallEdgeFromChara(AEndCharacter* InCharacter, float& OutDistance, float InRadius, bool InForceSSizeNav, bool InDrawDebug, float InDrawDebugTime);
    
    UFUNCTION(BlueprintCallable)
    static bool ExistsNavmeshWallEdge(FVector InLocation, float& OutDistance, AEndCharacterBase* InExecutor, float InRadius, bool InDrawDebug, float InDrawDebugTime);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool ExistDamageSourceRevive();
    
    UFUNCTION(BlueprintCallable)
    static void ExcludeActorsFromSkillCameraSlow(int32 sequenceActorUID, TArray<AActor*> Actors);
    
    UFUNCTION(BlueprintCallable)
    static void ExcludeActorFromSkillCameraSlow(int32 sequenceActorUID, AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static void EndForceFieldMode();
    
    UFUNCTION(BlueprintCallable)
    static void EndBurst(AEndCharacter* Character, bool instant);
    
    UFUNCTION(BlueprintCallable)
    static void EndBreakTime(AEndCharacter* Character, bool immediatelyEndAction);
    
    UFUNCTION(BlueprintCallable)
    static void EndBattleDirection();
    
    UFUNCTION(BlueprintCallable)
    static void EnableDamageReactionOwnerSyncAction(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool Die(AEndCharacter* Character, AEndCharacter* causerCharacter, bool skipDirection);
    
    UFUNCTION(BlueprintCallable)
    static void DestroySupportFieldAll();
    
    UFUNCTION(BlueprintCallable)
    static void DestroySafeAreaBehindDamageSource(int32 InGroupId, const TArray<FName>& InDamageSourceIdList);
    
    UFUNCTION(BlueprintCallable)
    static void DestroyDamageSourceAllCharacter(AEndCharacter* Character, bool bDestroyEffect, bool forceDestroy);
    
    UFUNCTION(BlueprintCallable)
    static void DestroyDamageSourceAll(bool bDestroyEffect);
    
    UFUNCTION(BlueprintCallable)
    static void DestroyDamageSource(FName DamageSourceID, AEndCharacter* ownerCharacter, bool bDestroyEffect, bool forceDestroy);
    
    UFUNCTION(BlueprintCallable)
    static int32 DecBattleSceneCount(FName InName);
    
    UFUNCTION(BlueprintCallable)
    static void DebugSetPropertyInformation(AEndCharacter* InCharacter, const FString& InName);
    
    UFUNCTION(BlueprintCallable)
    static void DebugSetHP(AEndCharacter* Chara, int32 HP);
    
    UFUNCTION(BlueprintCallable)
    static void CreateSyncActionOwnersByName(FName syncActionID0, FName ownerCharaName0, FName syncActionID1, FName ownerCharaName1, FName syncActionID2, FName ownerCharaName2);
    
    UFUNCTION(BlueprintCallable)
    static void CreateSyncActionOwners(FName syncActionID0, AEndCharacter* ownerChara0, FName syncActionID1, AEndCharacter* ownerChara1, FName syncActionID2, AEndCharacter* ownerChara2);
    
    UFUNCTION(BlueprintCallable)
    static void CreateSyncAction(FName SyncActionID, AEndCharacter* OwnerChara, AEndCharacter* targetChara, bool bPlayFromLoop, bool bOverwrite);
    
    UFUNCTION(BlueprintCallable)
    static void CreateSafeAreaBehindDamageSource(int32 InGroupId, const TArray<FName>& InDamageSourceIdList, AActor* InDangerActor);
    
    UFUNCTION(BlueprintCallable)
    static void CreateDamageSource(FName DamageSourceID, AEndCharacter* ownerCharacter, AEndCharacter* TargetCharacter, FName AbilityId, bool bOverrideDamage, int32 OverrideDamage);
    
    UFUNCTION(BlueprintCallable)
    static void CloseSummonEnvironment();
    
    UFUNCTION(BlueprintCallable)
    static void ClearEffectsByCategoryBattle();
    
    UFUNCTION(BlueprintCallable)
    static void ClearBPDamageCoefficient(AEndCharacter* Character);
    
    UFUNCTION(BlueprintCallable)
    static void ClearBattleCameraRestrictedPlayOwners();
    
    UFUNCTION(BlueprintCallable)
    static void ChangePositionOfSummonOmen(int32 PhaseNumber, AEndCharacter* ownerCharacter);
    
    UFUNCTION(BlueprintCallable)
    static void ChangePartyMember(TArray<FEndMenuJoin> changeParameters, bool showUI);
    
    UFUNCTION(BlueprintCallable)
    static void ChangeAppearance(AEndCharacter* Character, int32 Index);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool CanSyncAction(AEndCharacter* Chara);
    
    UFUNCTION(BlueprintCallable)
    static float CalcAimTargetOffsetHeight(FVector From, FVector To, float Velocity, float GravityScale, bool bDebugDraw, float DebugDrawTime);
    
    UFUNCTION(BlueprintCallable)
    static bool BreakParts(AEndCharacter* ownerCharacter, FName uniqueName, bool forceDisableBattleLog, bool forceDisableDamageSource);
    
    UFUNCTION(BlueprintCallable)
    static void BeginForceFieldMode(bool actorModeBattle, bool bDeactivateBattleCamera);
    
    UFUNCTION(BlueprintCallable)
    static void BeginBreak(AEndCharacter* Character, FName battleBreakID);
    
    UFUNCTION(BlueprintCallable)
    static void BeginBattleDirection(bool suspend);
    
    UFUNCTION(BlueprintCallable)
    static void AddStatusChangeID(AEndCharacter* Character, FName statusChangeID, EEndBattleStatusChangeTimeType timeType, bool ignoreResist, AEndCharacter* causeCharacter, bool Lock);
    
    UFUNCTION(BlueprintCallable)
    static void AddSpecialStatusChangeID(AEndCharacter* Character, AEndCharacter* causerCharacter, FName ID);
    
    UFUNCTION(BlueprintCallable)
    static void AddSpecialStateEffectWithBeamTarget(AEndCharacter* Character, FName specialStateEffectID, TArray<AEndCharacter*> beamTargetCharaList, bool bLineEffect, float LineEffectTangentLength);
    
    UFUNCTION(BlueprintCallable)
    static void AddSpecialStateEffect(AEndCharacter* Character, FName specialStateEffectID);
    
    UFUNCTION(BlueprintCallable)
    static void AddInvincibleThroughAbilityID(AEndCharacter* Character, FName AbilityId);
    
    UFUNCTION(BlueprintCallable)
    static void AddImpluse(AEndCharacter* Character, FVector Direction, float Magnitude);
    
    UFUNCTION(BlueprintCallable)
    static void AddIgnoreDamageSourceLookAtTraceActor(AEndCharacter* Character, AActor* IgnoreActor);
    
    UFUNCTION(BlueprintCallable)
    static void AddEnableTargetAbility(AEndCharacter* Character, FName AbilityId);
    
    UFUNCTION(BlueprintCallable)
    static void AddDangerSource(AEndCharacter* Instigator, float Duration, const TArray<FEndAIDangerInfo>& Infos, bool bResolveWithDamageSource);
    
    UFUNCTION(BlueprintCallable)
    static void AddCombinationGauge(AEndCharacter* Character, int32 Value);
    
    UFUNCTION(BlueprintCallable)
    static int32 AddBattleSceneCount(FName InName, int32 InAddCount);
    
    UFUNCTION(BlueprintCallable)
    static void AddBattleCameraRestrictedPlayOwners(TArray<AEndCharacterBase*> restrictedPlayOwners);
    
    UFUNCTION(BlueprintCallable)
    static void AddAttachEffect(AEndCharacter* Chara, FEndCharacterAttachEffectArguments args);
    
    UFUNCTION(BlueprintCallable)
    static void ActiveRagdoll(AEndCharacter* Character, bool bImmediately);
    
};

