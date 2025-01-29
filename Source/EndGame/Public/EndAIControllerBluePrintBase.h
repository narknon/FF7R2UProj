#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EEndBattleAbilityCommandType.h"
#include "EEndBattleAttributeType.h"
#include "EEndBattleCountLogType.h"
#include "EEndBattleSpecialStatusChangeType.h"
#include "EEndBattleSyncActionStateType.h"
#include "EPlayerType.h"
#include "EndDataObjectBattleAbilityAccessor.h"
#include "EndDataObjectBattleDamageSourceAccessor.h"
#include "Engine/LatentActionManager.h"
#include "EActorMoveMode.h"
#include "EEndAIBranchBit.h"
#include "EEndAIExecPinBranch.h"
#include "EEndAiBattleTargetType.h"
#include "EEndAiMathBinCmp.h"
#include "EEndAiMathCmp.h"
#include "EEndBattleAbilityReactionConditionType.h"
#include "EEndBattleAttackDirectionType.h"
#include "EEndBattleDefenseGuardType.h"
#include "EEndBattleReactionNotificationType.h"
#include "EEndBattleUniqueAbilitySpawnWeaponType.h"
#include "EEndCharacterControllerStateType.h"
#include "EEndDoOnceCode.h"
#include "EEndDoOnceOutCode.h"
#include "EWeaponSlot.h"
#include "EndAIActionPackReturnInfo.h"
#include "EndAIController.h"
#include "EndBattleTargetJumpBurstInput.h"
#include "EndCharacterAttachEffectArguments.h"
#include "Templates/SubclassOf.h"
#include "EndAIControllerBluePrintBase.generated.h"

class AActor;
class AEndCharacter;
class AEndCharacterBase;
class UAnimSequence;
class UEndAIAbilityDefinitionReactionCounter;
class UEndAIActionDefinitionBase;
class UEndAIActionPackBase;
class UEndAIAvoidDefinitionReaction;
class UEndAIComboDefinitionReactionCounter;
class UEndAIGuardDefinitionReaction;
class UEndAIMoveDefinition;
class UEndAITransDefinition;
class UEnvQuery;
class UObject;

UCLASS(Blueprintable, MinimalAPI)
class AEndAIControllerBluePrintBase : public AEndAIController {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEnvQuery* FollowTeleportEQS;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEnvQuery* FollowTeleportEQS_BuggyGetOff;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEnvQuery* FollowTeleportEQS_SequencerPv;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEnvQuery* FollowTeleportEQS_FastTravel;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FollowMoveRateDash;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FollowMoveRateRun;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FollowMoveRateJog;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FollowMoveRateWalk;
    
public:
    AEndAIControllerBluePrintBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    bool ToggleDebugEditMode();
    
    UFUNCTION(BlueprintCallable)
    void TestUniqueStalker();
    
    UFUNCTION(BlueprintCallable)
    void TestMoveTo_AIState(FVector InVector);
    
    UFUNCTION(BlueprintCallable)
    void TestFollowStalker();
    
    UFUNCTION(BlueprintCallable)
    void TestFollowForceMainFollow();
    
    UFUNCTION(BlueprintCallable)
    void TestFollowFastTravel();
    
    UFUNCTION(BlueprintCallable)
    void TestFollowDate();
    
    UFUNCTION(BlueprintCallable)
    void TestFollowChocoboFree();
    
    UFUNCTION(BlueprintCallable)
    void StartFollowBackwardLeaveLeaderToPoint_Test();
    
    UFUNCTION(BlueprintCallable)
    void SetVisibilityWeapon(bool bVisible, EWeaponSlot weaponSlotType);
    
    UFUNCTION(BlueprintCallable)
    void SetSpecialStatusStateChangeID(EEndBattleSpecialStatusChangeType Type, FName stateChangeID, FName paramID);
    
    UFUNCTION(BlueprintCallable)
    void SetPushCollisionEnable(FName partId, bool Enable);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideUpperAnim(const FName InName, const FName InInterIn, const FName InInterOut);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideKeepFromAbility(FName InAbilityName);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideKeep(int32 InKeep);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideActiveAimAngle(FVector2D ActiveYawRange, FVector2D ActivePitchRange);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideAbilityKeep(int32 Value);
    
    UFUNCTION(BlueprintCallable)
    void SetMeshDisp(bool InDisp);
    
    UFUNCTION(BlueprintCallable)
    void SetHPPercent(int32 Percent);
    
    UFUNCTION(BlueprintCallable)
    void SetForceDefaultCollisionSetting();
    
    UFUNCTION(BlueprintCallable)
    void SetEnabledUpdateAimLocation(bool bEnabled);
    
    UFUNCTION(BlueprintCallable)
    void SetDisableSuspendAction(bool Disable);
    
    UFUNCTION(BlueprintCallable)
    void SetDisableResidualParticlesAbility(bool Disable);
    
    UFUNCTION(BlueprintCallable)
    void SetDisableReaction(bool Disable);
    
protected:
    UFUNCTION(BlueprintCallable)
    void SetCharacterRotation(FRotator InRotation);
    
    UFUNCTION(BlueprintCallable)
    void SetCharacterLocation(FVector InLocation, bool bTeleportPhysics);
    
public:
    UFUNCTION(BlueprintCallable)
    void SetCapturableBySummon(bool Flag);
    
    UFUNCTION(BlueprintCallable)
    void SetBattleSafeTransform(bool bEnable);
    
    UFUNCTION(BlueprintCallable)
    void SendBPMessageToBattleScene(AEndCharacter* SendCharacter, const FName& Message);
    
    UFUNCTION(BlueprintCallable)
    void ResetTrans();
    
    UFUNCTION(BlueprintCallable)
    void ResetOverrideUpperAnim(bool InPlayEndAnim);
    
    UFUNCTION(BlueprintCallable)
    void ResetOverrideKeep();
    
    UFUNCTION(BlueprintCallable)
    void ResetOverrideActiveAimAngle();
    
    UFUNCTION(BlueprintCallable)
    bool RequestTrans(TSubclassOf<UEndAITransDefinition> TransDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    bool RequestTakeDamageCounterCombo(TSubclassOf<UEndAIComboDefinitionReactionCounter> ComboCounterDefinitionClass, AEndCharacter* CauserChara, FName AbilityId, EEndBattleAbilityCommandType CommandType, FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    bool RequestTakeDamageCounterAndMove(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, FName AbilityId, EEndBattleAbilityCommandType CommandType, FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    bool RequestTakeDamageCounter(TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, FName AbilityId, EEndBattleAbilityCommandType CommandType, FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    bool RequestReactionGuard(TSubclassOf<UEndAIGuardDefinitionReaction> GuardDefinitionClass, AEndCharacter* CauserChara, int32 HandleId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestReactionCounterCombo(TSubclassOf<UEndAIComboDefinitionReactionCounter> ComboCounterDefinitionClass, AEndCharacter* CauserChara, int32 HandleId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestReactionCounterAndMove(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, int32 HandleId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestReactionCounter(TSubclassOf<UEndAIAbilityDefinitionReactionCounter> CounterDefinitionClass, AEndCharacter* CauserChara, int32 HandleId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestReactionAvoid(TSubclassOf<UEndAIAvoidDefinitionReaction> AvoidDefinitionClass, AEndCharacter* CauserChara, int32 HandleId);
    
    UFUNCTION(BlueprintCallable)
    void RequestPlayBattleCameraSequence(FName CameraSequenceID, AEndCharacterBase* OwnerChara, AEndCharacterBase* HasResourceChara, AActor* TargetActor, bool bIsToRegisterSlaveViewOnly, float MassiveEnvironmentFrustrumScaleForMainPass);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestGuardHitCounterPackArrayLot(FName DefenseID, bool bExecuteTiming, TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList, TArray<int32> LotProbabilities);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestGuardHitCounterPackArray(FName DefenseID, bool bExecuteTiming, TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestGuardHitCounterPack(FName DefenseID, bool bExecuteTiming, TSubclassOf<UEndAIActionPackBase> ActionPackClass);
    
    UFUNCTION(BlueprintCallable)
    bool RequestGuardHitCounter(FName DefenseID, bool bExecuteTiming, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    bool RequestCombinationSpecial(TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass, bool bLast);
    
    UFUNCTION(BlueprintCallable)
    bool RequestCancelReactionAvoidToAction(TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    void RequestAttachSyncAction();
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestActionPackArrayLot(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList, TArray<int32> LotProbabilities);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestActionPackArray(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestActionPack(TSubclassOf<UEndAIActionPackBase> ActionPackClass);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestActionInterruptPackArrayLot(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList, TArray<int32> LotProbabilities);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestActionInterruptPackArray(TArray<TSubclassOf<UEndAIActionPackBase>> ActionPackClassList);
    
    UFUNCTION(BlueprintCallable)
    FEndAIActionPackReturnInfo RequestActionInterruptPack(TSubclassOf<UEndAIActionPackBase> ActionPackClass);
    
    UFUNCTION(BlueprintCallable)
    bool RequestActionInterrupt(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    bool RequestActionChild(TSubclassOf<UEndAIActionDefinitionBase> InActionDefinitionClass, FName ChildActionId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestAction(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    void RemoveSpecialStatusByID(FName ID);
    
    UFUNCTION(BlueprintCallable)
    void RemoveSpecialStateEffect(FName specialStateEffectID);
    
    UFUNCTION(BlueprintCallable)
    void RemoveAttachEffect(const FName AttachSocketName, const FName ResourceName, bool bDestroy);
    
    UFUNCTION(BlueprintCallable)
    int32 PlayBattleCameraSequence(FName SequenceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OverrideDamageHitReactionID(FName AbilityId, FEndDataObjectBattleAbilityAccessor dataObjectBattleAbility, FName DamageSourceID, bool abilityFirstHit, AEndCharacter* causerCharacter, FName& damageHitReactionID);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnUseAbilityInvoke(FName AbilityId);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnUseAbility(AEndCharacter* useCharacter, FName AbilityId);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnUpdateBattle(float DeltaTime);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakePartsDamage(const FName& BattleCharaPartsSpecID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeDamageOverTime(int32 Damage);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeDamageInvoke(int32 Damage, AEndCharacter* InChara, FName InName, EEndBattleAbilityCommandType InCommandType, bool InBind, bool InGuard, FName InBoneName, bool InAttributeWeak, FName InDmgSrcID, EEndBattleAttributeType appendAttribute, float justHitRotYaw, FVector hitPosition, bool InHeal, bool InCounter, FEndDataObjectBattleDamageSourceAccessor dataObjectBattleDamageSource, bool useAbilityUCPC, FEndDataObjectBattleAbilityAccessor dataObjectBattleAbility);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeDamageHPFirstInvoke(AEndCharacter* causerCharacter, FName AbilityId, bool attributeWeak, EEndBattleAbilityCommandType AbilityCommandType, FEndDataObjectBattleAbilityAccessor dataObjectBattleAbility);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeDamageHPCutValueOver50First(AEndCharacter* causerCharacter, FName AbilityId, FEndDataObjectBattleAbilityAccessor dataObjectBattleAbility, int32 attackCount, FEndDataObjectBattleDamageSourceAccessor dataTableBattleDamageSource);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeAbilityInvoke(AEndCharacter* CauserChara, const FName& AbilityName, EEndBattleAbilityCommandType AbilityCommandType, const TArray<FName>& AnimationNameList);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSystemMessage(const FString& InMessage);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSyncActionRescue(const FName& SyncActionID, AEndCharacter* targetChara);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSummonCutSceneEnd();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSummonCutSceneBegin();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStolen(AEndCharacter* causerCharacter);
    
    UFUNCTION(BlueprintCallable)
    void OnStartSequencerPV_Test2();
    
    UFUNCTION(BlueprintCallable)
    void OnStartSequencerPV_Test();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartBattleInvoke();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSpecialStatusChange(const FName& SpecialStatusChangeID, EEndBattleSpecialStatusChangeType Type, const FName& ChangeID, const TArray<float>& Params, const TArray<FName>& ParamIDs, const TArray<AActor*>& ParamActors);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnSpecialStateEffectEvent(FName EventName);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnRemoveStatusChangeID(FName statusChangeID);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnReactionSensingTakeAbilityInvoke(AEndCharacter* CauserChara, int32 HandleId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnReactionSensingInvoke(AEndCharacter* CauserChara, int32 HandleId, EEndBattleReactionNotificationType NotificationType, EEndBattleAttackDirectionType AttackDirectionType);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPreTakeDamage(float justHitRotYaw, AEndCharacter* ownerCharacter, FName InName, FName hitBoneName, FName DamageSourceID, const FVector& hitPosition, int32 Damage, bool InGuard, EEndBattleAttributeType appendAttribute, FEndDataObjectBattleDamageSourceAccessor dataObjectBattleDamageSource, bool heal);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPrepareAsset();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPreEndBattleInvoke();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPreBurstBegin();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlayBattleCameraSequence(int32 sequenceActorUID, FName battleCameraSequenceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPCDead(EPlayerType PlayerType, int32 alivePCNum);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPartsBreak(FName PartsID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMotionStateMessageUpdate(FName InMotionName, FName InName, int32 InIntValue, float InFloatValue, float InProgress, bool LatestContactWall, bool LatestContact);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMotionStateMessageEnd(FName InMotionName, FName InName, int32 InIntValue, float InFloatValue);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMotionStateMessageBegin(FName InMotionName, FName InName, int32 InIntValue, float InFloatValue, float InTotalDuration);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMotionMessageInvoke(FName InMotionName, FName InName, int32 InIntValue, float InFloatValue);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnKilledInvoke(int32 Damage, AEndCharacter* InTarget, FName InName, bool InBind);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnIncrementBattleCountPerID(FName TargetCharaName, EEndBattleCountLogType Type, FName ID, int32 Count);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void OnHitDamageSource(bool& outDestroySrcDamageSoruce, const FName& SrcDamageSourceID, const FName& HitDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnGiveDamageInvoke(int32 Damage, AEndCharacter* InTarget, FName InName, bool InBind, bool InGuard, bool KeepOver, bool InCounter, FName InBoneName, bool InAttributeWeak, FName InDamageSourceID, bool InSteal, bool heal, bool kill, bool justGuard, bool bLock);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool OnGetTargetFieldPosition(FVector& OutPosition, FName InBattleAbilityID, FName InDamageSourceID, FName InAnimationName);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    AActor* OnGetTargetFieldActor(FName InBattleAbilityID);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool OnGetCreateFieldPosition(FVector& OutPosition, FQuat& outQuat, FName InBattleAbilityID, FName InDamageSourceID, FName InAnimationName);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool OnGetAbilityJumpLandLocationAndRotation(FVector& OutLocation, FRotator& OutRotation, FName InBattleAbilityID);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool OnGetAbilityJumpLandLocation(FVector& OutLocation, FName InBattleAbilityID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnFieldActionInfoFromPlayerInvoke(FName ActionTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEnemySummonCutSceneEnd();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEnemySummonCutSceneBegin();
    
    UFUNCTION(BlueprintCallable)
    void OnEndSequencerPV_Test();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndCutSceneNextFrameInvoke(const FName& CutSceneID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndCutSceneInvoke(const FName& CutSceneID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndBurst(bool instant);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndBreak();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndBattleInvoke();
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndAbilityInvoke(FName AbilityId, bool createdDamageSource, bool suspended, bool suspendedSummonCutScene);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDestroyDamageSource(const FName& DamageSourceID, const FVector& Location, const FQuat& Quat);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDefenseGuardReflectDamage(FName battleDefenseID, AEndCharacter* attackedCharacter, FEndDataObjectBattleAbilityAccessor attackedDataObjectBattleAbility, const FName& attackedDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDefenseGuardDamageHPFirst(FName battleDefenseID, EEndBattleDefenseGuardType defenseGuardType, bool executeTiming, AEndCharacter* attackedCharacter, FEndDataObjectBattleAbilityAccessor attackedDataObjectBattleAbility, const FName& attackedDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDefenseGuard(FName battleDefenseID, EEndBattleDefenseGuardType defenseGuardType, bool executeTiming, AEndCharacter* attackedCharacter, FEndDataObjectBattleAbilityAccessor attackedDataObjectBattleAbility, const FName& attackedDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDead(bool AtBurst);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCutSceneMessageInvoke(const FName& Message);
    
    UFUNCTION(BlueprintCallable)
    void OnCutChangeSequencerPV_Test(bool bEndShot);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCreateDamageSource(AEndCharacter* InOwner, const FName& DamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCreateCharacterControllerComponentBattle();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCharacterControllerChangeState(EEndCharacterControllerStateType BeforeState, EEndCharacterControllerStateType AfterState);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangeSyncActionState(const FName& SyncActionID, EEndBattleSyncActionStateType StateType, AEndCharacter* targetChara, const FName& DetachDamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangeLeader(AEndCharacter* LeaderCharacter);
    
    UFUNCTION(BlueprintCallable)
    void OnCameraBlendOutSequencerPV_Test();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginCutSceneInvoke(const FName& CutSceneID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginBurst();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginBreak(AEndCharacter* causerCharacter);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAIMoveModeChanged(EActorMoveMode BeforeMode, EActorMoveMode AfterMode);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAddStatusChangeID(FName statusChangeID);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAbilityReactionConditionTargetDodgeDirection(const FName& AbilityId, AEndCharacter* targetChara);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAbilityReactionConditionTargetDodge(const FName& AbilityId, AEndCharacter* targetChara);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAbilityReactionCondition(EEndBattleAbilityReactionConditionType abilityReactionConditionType);
    
    UFUNCTION(BlueprintCallable)
    void NotifyAbilityReaction(float Param0);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsRangeArea2D(AEndCharacter* InChara, FVector InLocation, float InRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsOverrideUpperAnim();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInSyncAction() const;
    
    UFUNCTION(BlueprintCallable)
    void IsInRangeToTargetBranch(float InMin, float InMax, EEndAiMathBinCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal, bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInRangeToTarget(float InMin, float InMax, bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInDummyBattle() const;
    
    UFUNCTION(BlueprintCallable)
    void IsInAngleToTargetBranch(float InAngle, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal, bool InReverse);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInAngleToTarget(float InAngle, bool InReverse);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsIdle();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsHPPercent(int32 Percent, EEndAiMathCmp Cmp);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsForceTeleportingFollowAIPartyMemberAll();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsExistSpawnWeaponCharacter(EEndBattleUniqueAbilitySpawnWeaponType spawnWeaponType, FName uniqueWeaponName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsEditor() const;
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsDelayProcessing();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsDebugEditMode() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActionRestriction();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool HasSpecialStatusByID(FName ID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool HasSpecialStatus(EEndBattleSpecialStatusChangeType Type);
    
    UFUNCTION(BlueprintCallable)
    bool HasDamageSource(FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetVectorToTarget();
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool GetTargetJumpBurstInput(FEndBattleTargetJumpBurstInput& Input);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetTarget() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<AEndCharacter*> GetSyncActionCharacter(TEnumAsByte<EEndAiBattleTargetType::Type> InTarget);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    void GetSpecialStatusType(TArray<EEndBattleSpecialStatusChangeType>& typeList) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetSpecialStatusParamFloat(EEndBattleSpecialStatusChangeType Type, FName paramID) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<AEndCharacter*> GetSpecialStatusChangeCharacter(TEnumAsByte<EEndAiBattleTargetType::Type> InTarget, EEndBattleSpecialStatusChangeType Type);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetSpawnWeaponCharacter(EEndBattleUniqueAbilitySpawnWeaponType weaponType, FName uniqueWeaponName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetPlayerLeader();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetPathDistanceFromTarget(FVector Location);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetPathDistance(FVector Location);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetNearestOpponentDistance(bool bIgnoreCharacterRadius);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetLocationAngleAbs(FVector Loc, AEndCharacter* Target) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetLocationAngle(FVector Loc, AEndCharacter* Target) const;
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetLeader();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetHPPercent();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetHPMax();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetHeightDistanceToTarget(bool bAbs);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool GetFirstDamageTime(float& FirstDamageTime, const UAnimSequence* AnimSequecne, float StartTime) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetDistanceToTarget2D(bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetDistanceToTarget(bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetDistanceToCharacter2D(AEndCharacter* InCharacter, bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetDistanceToCharacter(AEndCharacter* InCharacter, bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetCharaSpecName();
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FRotator GetCharacterRotation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetCharacterLocation() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetCharacterFeetLocation() const;
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetCharacter();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAngleToTarget(bool bAbs);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool GetAbilityLoopMoveStartSpecifiedTargetLocation(FVector& OutLocation, FName AbilityId);
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool GetAbilityLoopMoveNextSpecifiedTargetLocation(FVector& OutLocation, FName AbilityId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void GetAbilityAimTargetPointName(FName& outTargetPointName);
    
    UFUNCTION(BlueprintCallable)
    bool ForceTeleportFollowAIPartyMemberAll();
    
    UFUNCTION(BlueprintCallable)
    void ForceDisableAimEffectorSetting(FName EffectorSettingName);
    
    UFUNCTION(BlueprintCallable)
    void EndFollowBackwardLeaveLeaderToPoint_Test();
    
    UFUNCTION(BlueprintCallable)
    void EnableDamageReactionOwnerSyncAction();
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"))
    void DoOnceWithThen(const EEndDoOnceCode Code, FLatentActionInfo LatentInfo, EEndDoOnceOutCode& Result);
    
    UFUNCTION(BlueprintCallable)
    void DestroyDamageSource(FName DamageSourceID, bool bDestroyEffect);
    
    UFUNCTION(BlueprintCallable)
    void DebugLocalLog(const FString& inString, FLinearColor TextColor);
    
    UFUNCTION(BlueprintCallable)
    void DebugEditModeBranch(EEndAIExecPinBranch& PinBranch);
    
protected:
    UFUNCTION(BlueprintCallable)
    void DeactivatePBDConstraint(float BlendTime);
    
public:
    UFUNCTION(BlueprintCallable)
    void CreateSyncAction(FName SyncActionID, AEndCharacter* targetChara, bool bOverwrite);
    
    UFUNCTION(BlueprintCallable)
    void CreateDamageSource(FName DamageSourceID, AEndCharacter* targetChara, FName AbilityId, bool bOverrideDamage, int32 OverrideDamage);
    
    UFUNCTION(BlueprintCallable)
    void CheckDistanceToTargetBranch(float InDistance, EEndAiMathCmp Cmp, TEnumAsByte<EEndAIBranchBit::Type>& OutSignal, bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool CheckDistanceToTarget(float InDistance, EEndAiMathCmp Cmp, bool bIgnoreCharacterRadius);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool CanSeeTarget(bool bValidBlock);
    
    UFUNCTION(BlueprintCallable)
    void CancelActionChild(FName ChildActionId);
    
protected:
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    void AIDelay(UObject* WorldContextObject, float Duration, FLatentActionInfo LatentInfo);
    
public:
    UFUNCTION(BlueprintCallable)
    void AddSpecialStatusByID(FName ID);
    
    UFUNCTION(BlueprintCallable)
    void AddSpecialStateEffectWithBeamTarget(FName specialStateEffectID, TArray<AEndCharacter*> beamTargetCharaList);
    
    UFUNCTION(BlueprintCallable)
    void AddSpecialStateEffect(FName specialStateEffectID);
    
    UFUNCTION(BlueprintCallable)
    void AddAttachEffect(FEndCharacterAttachEffectArguments args);
    
protected:
    UFUNCTION(BlueprintCallable)
    void ActivatePBDConstraint(float BlendTime);
    
};

