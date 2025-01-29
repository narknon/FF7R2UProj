#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EActorMoveMode.h"
#include "EEndAIActionMoveTimeOut.h"
#include "EEndAIActionState.h"
#include "EEndAIBattleGroupNotify.h"
#include "EEndAIEnemyCombinationNotify.h"
#include "EEndAIEnemyTargetSelectConditionCategory.h"
#include "EEndAIIntervalType.h"
#include "EEndAIProwlCallType.h"
#include "EEndBattleAbilityActionCategory.h"
#include "EndAIBattleEnemyTargetSelectConditionData.h"
#include "EndAIBattleExtraInterval.h"
#include "EndAIBattleGroupNotifyInfo.h"
#include "EndAIBattleGroupSetting.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndAIDefinitionReturnTag.h"
#include "EndAIEnemyCautionSetting.h"
#include "EndAIEnemyFieldSetting.h"
#include "EndAIEnemyFieldSetting_Territory.h"
#include "Templates/SubclassOf.h"
#include "EndAIControllerEnemyBase.generated.h"

class AEndCharacter;
class UEndAIAbilityDefinition;
class UEndAIActionDefinition;
class UEndAIActionDefinitionBase;
class UEndAIComboDefinition;
class UEndAIFieldDefinitionBase;
class UEndAIMoveDefinition;

UCLASS(Blueprintable, MinimalAPI)
class AEndAIControllerEnemyBase : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LightAttackInterval;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LightAttackIntervalWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HardAttackInterval;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HardAttackIntervalWidth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIBattleExtraInterval> ExtraIntervals;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableReturnToBattleArea;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIEnemyCautionSetting m_CautionSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> m_ReturnHomeMoveDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIBattleGroupSetting> GroupSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupIndividualTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EEndAIEnemyTargetSelectConditionCategory, FEndAIBattleEnemyTargetSelectConditionData> TargetSelectConditions;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNotUseFieldDefinition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIEnemyFieldSetting> DefaultFieldSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIFieldDefinitionBase> DefaultReturnFieldDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIEnemyFieldSetting_Territory> TerritoryFieldSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseFieldEQSTerritoryFilter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName drawThinkPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bActiveAITimerToDebugMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDisableBattleAreaErrorLog;
    
public:
    AEndAIControllerEnemyBase(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable)
    int32 ToRestoreParts(FName keyword);
    
    UFUNCTION(BlueprintCallable)
    void ToRepairWithHPPercent(FName charaPartsSpecName, FName meshLabelName, float HPPercent);
    
public:
    UFUNCTION(BlueprintCallable)
    int32 ToDestructionParts(FName keyword);
    
protected:
    UFUNCTION(BlueprintCallable)
    bool ToChangeParts(FName MeshName, FName MeshLabel);
    
    UFUNCTION(BlueprintCallable)
    void ToBreak(FName charaPartsSpecName);
    
    UFUNCTION(BlueprintCallable)
    void TemporaryWithdrawalGroup(FName InGroupId);
    
public:
    UFUNCTION(BlueprintCallable)
    void StopExtraIntervalAll();
    
    UFUNCTION(BlueprintCallable)
    void StopExtraInterval(FName ID);
    
    UFUNCTION(BlueprintCallable)
    void StopAITimer(FName ID);
    
    UFUNCTION(BlueprintCallable)
    void StartExtraInterval(FName ID);
    
protected:
    UFUNCTION(BlueprintCallable)
    bool StartBurst(bool Force);
    
public:
    UFUNCTION(BlueprintCallable)
    void StartAITimer(FName ID, float Time);
    
    UFUNCTION(BlueprintCallable)
    void SetTopPriorityActionConditionResult(FName TopPriorityActionId, int32 Priority, bool bResult);
    
protected:
    UFUNCTION(BlueprintCallable)
    void SetReserveWarpDefinitionTargetPointNames(TArray<FName> TargetPointNames);
    
    UFUNCTION(BlueprintCallable)
    void SetReserveWarpDefinitionTargetLocations(TArray<FVector> Locations);
    
    UFUNCTION(BlueprintCallable)
    void SetReserveMoveToMultiPointDefinitionTargetLocations(TArray<FVector> Locations);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideBattleCharaSpec(FName BattleCharaSpecID);
    
    UFUNCTION(BlueprintCallable)
    void SetOverrideBattleCharaPartsSpec(FName BaseID, FName OverrideId, bool bChangeHP);
    
public:
    UFUNCTION(BlueprintCallable)
    void SetNextWarpPosition(const FVector& WarpPosition);
    
protected:
    UFUNCTION(BlueprintCallable)
    void SetLockTargetBP(AEndCharacter* Target, bool bImmediate);
    
    UFUNCTION(BlueprintCallable)
    void SetIgnoreRightToAttack(bool bIgnore);
    
public:
    UFUNCTION(BlueprintCallable)
    void SetHPMinLimitPercent(int32 InPercent);
    
protected:
    UFUNCTION(BlueprintCallable)
    void SetExtraConditionResult(FName ConditionTag, bool bResult);
    
    UFUNCTION(BlueprintCallable)
    void SetDisableTargetPoint(FName SocketName, bool bDisable);
    
    UFUNCTION(BlueprintCallable)
    void SetDisableBurst(bool Disable);
    
    UFUNCTION(BlueprintCallable)
    void SetDisableBPDamage(bool Disable);
    
    UFUNCTION(BlueprintCallable)
    void SetDefinitionLockTargetResult(FName LockTargetTag, AEndCharacter* Target);
    
    UFUNCTION(BlueprintCallable)
    void SetBurstForceAerial(bool Flag);
    
    UFUNCTION(BlueprintCallable)
    void SetBPPercent(float Value);
    
    UFUNCTION(BlueprintCallable)
    void SetBPDamageCoefficient(float Coefficient);
    
    UFUNCTION(BlueprintCallable)
    void SetBPAttackChance(bool Enable);
    
    UFUNCTION(BlueprintCallable)
    void SetBP(float Value);
    
    UFUNCTION(BlueprintCallable)
    void SetBodyDummyParts(FName PartsID);
    
    UFUNCTION(BlueprintCallable)
    void SetBGFAStatus(FName AccessorID, FName StateId);
    
    UFUNCTION(BlueprintCallable)
    void SetAngleRangeTargetPoint(FName SocketName, float baseAngle, float angleRange);
    
    UFUNCTION(BlueprintCallable)
    void SetAIActionStatusRecastTime(TArray<TSubclassOf<UEndAIActionDefinition>> ActionDefClassList, float RecastTime);
    
    UFUNCTION(BlueprintCallable)
    void SendGroupMessage(FName Message, EEndAIBattleGroupNotify NotifyType, FName GroupId, FName IndividualTag);
    
public:
    UFUNCTION(BlueprintCallable)
    void SelfDisappear(bool drawPause);
    
    UFUNCTION(BlueprintCallable)
    void RewriteExtraInterval(FName ID, float Interval, float IntervalWidth);
    
    UFUNCTION(BlueprintCallable)
    void RewriteAttackInterval(EEndAIIntervalType IntervalType, float Interval, float IntervalWidth);
    
protected:
    UFUNCTION(BlueprintCallable)
    void ReturnGroup(FName InGroupId);
    
public:
    UFUNCTION(BlueprintCallable)
    void RestartExtraIntervalAll();
    
    UFUNCTION(BlueprintCallable)
    void RestartExtraInterval(FName ID);
    
    UFUNCTION(BlueprintCallable)
    void RestartAttackIntervalAll();
    
    UFUNCTION(BlueprintCallable)
    void RestartAttackInterval(EEndAIIntervalType IntervalType);
    
    UFUNCTION(BlueprintCallable)
    bool RestartAITimer(FName ID);
    
protected:
    UFUNCTION(BlueprintCallable)
    void ResetOverrideBattleCharaSpec();
    
    UFUNCTION(BlueprintCallable)
    void ResetOverrideBattleCharaPartsSpec(FName BaseID);
    
    UFUNCTION(BlueprintCallable)
    void ResetLockTargetBP();
    
public:
    UFUNCTION(BlueprintCallable)
    void ResetDefaultAttackInterval();
    
    UFUNCTION(BlueprintCallable)
    void ResetAttackIntervalElapsedTime(EEndAIIntervalType IntervalType);
    
protected:
    UFUNCTION(BlueprintCallable)
    void ResetAngleRangeTargetPoint(FName SocketName);
    
    UFUNCTION(BlueprintCallable)
    void ResetAIActionStatus(TArray<TSubclassOf<UEndAIActionDefinition>> ActionDefClassList, bool bTrialCount, bool TrialStraightCount, bool bRecastTime);
    
    UFUNCTION(BlueprintCallable)
    bool RequestStartCombinationTopPriority(TSubclassOf<UEndAIActionDefinitionBase> CombinationDefinitionClass, AEndCharacter* Target, FName TopPriorityActionId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestStartCombination(TSubclassOf<UEndAIActionDefinitionBase> CombinationDefinitionClass, AEndCharacter* Target);
    
    UFUNCTION(BlueprintCallable)
    void RequestShowPreloadedWaveReinforcement(FName territoryID, FName reinforcementActorName, FTransform reinforcementStartPoint);
    
    UFUNCTION(BlueprintCallable)
    bool RequestNotificationComboAbilityInterrupt(TSubclassOf<UEndAIAbilityDefinition> AbilityDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    bool RequestConnectActivatedAbilityCombo(TSubclassOf<UEndAIComboDefinition> ComboDefinitionClass, FName AbilityId);
    
    UFUNCTION(BlueprintCallable)
    bool RequestCombinationCombo(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIComboDefinition> ComboDefinitionClass, bool bLast);
    
    UFUNCTION(BlueprintCallable)
    bool RequestCombination(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIAbilityDefinition> AbilityDefinitionClass, bool bLast);
    
    UFUNCTION(BlueprintCallable)
    bool RequestActionTopPriority(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass, FName TopPriorityActionId);
    
public:
    UFUNCTION(BlueprintCallable)
    void PauseExtraIntervalAll();
    
    UFUNCTION(BlueprintCallable)
    void PauseExtraInterval(FName ID);
    
    UFUNCTION(BlueprintCallable)
    void PauseAttackIntervalAll();
    
    UFUNCTION(BlueprintCallable)
    void PauseAttackInterval(EEndAIIntervalType IntervalType);
    
    UFUNCTION(BlueprintCallable)
    bool PauseAITimer(FName ID);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTransInvoke(FName PrevTransId, FName NextTransId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartMoveDefinitionInvoke(FName MoveDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartAICombinationInvoke(FName CombinationId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartActionRestrictionInvoke();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartActionDefinitionInvoke(FName ActionDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnShowPreloadedWaveReinforcement(FName reinforcementActorName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnRemoveTrans_ReturnHomeInvoke(FName CurrentTransId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnRemoveTrans_EndBattleInvoke(FName CurrentTransId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnReactionAvoidCancelInvoke(FName AvoidDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnProwlInvoke(EEndAIProwlCallType CallType);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPreExecutWarpDefinitionInvoke(FName WarpDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnNotificationDefinitionComboInvoke(FName ComboDefTag, FName ActionDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMoveTimeOutInvoke(EEndAIActionMoveTimeOut TimeOutType, FName MoveDefTag, FName ActionDefTag, FName ComboDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnGroupMessageInvoke(FEndAIBattleGroupNotifyInfo NotifyInfo);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnFailPreActionCancelInvoke(FName ActionTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnExtraConditionInvoke(FName ConditionTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnExecutWarpDefinitionInvoke(FName WarpDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndMoveDefinitionInvoke(FName MoveDefTag, bool bSuspendSummonCutScene);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndAICombinationInvoke(FName CombinationId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndActionRestrictionInvoke();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndActionDefinitionInvoke(FName ActionDefTag, FName SuspendAbilityId, bool bSuspendSummonCutScene);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDefinitionLockTargetInvoke(FName LockTargetTag);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAITimerInvoke(FName ID);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAICombinationInvoke(EEndAIEnemyCombinationNotify NotifyType, FName CombinationId, int32 Count);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnActionTopPriorityInvoke(FName TopPriorityActionId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnActionInvoke(EEndAIIntervalType IntervalType, FName ExtraIntervalId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnActionInterruptInvoke(FName ActionTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnActionChildInvoke(FName ChildActionId);
    
    UFUNCTION(BlueprintCallable)
    void NotifyAbilitySuccessToTargetSystem_EN2219(AEndCharacter* Target, EEndBattleAbilityActionCategory ActionCategory);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsPlayingAICombination();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInHateLock();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsInBattleArea() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsGroupLeader(FName GroupId);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsDifficultyHard();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsDestruction(FName keyword);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsBurst();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsBPAttackChance();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsBGFAStatusBP(FName AccessorID, FName StateId);
    
    UFUNCTION(BlueprintCallable)
    bool IsAIActionStatusRecastForId(FName AIActionStatusId);
    
    UFUNCTION(BlueprintCallable)
    bool IsAIActionStatusRecast(TArray<TSubclassOf<UEndAIActionDefinition>> ActionDefClassList);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsAffiliatedGroup(AEndCharacter* Chara, FName GroupId);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsActiveAITimer(FName ID) const;
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetTransID();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetPhase() const;
    
protected:
    UFUNCTION(BlueprintCallable)
    int32 GetPartsHPPercent(FName PartsID);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetOwnerTerritoryIdBP() const;
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetNextWarpPosition();
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetMoveToMultiTargetName();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetGroupMembersNum(FName GroupId, bool bIgnoreLeader);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<AEndCharacter*> GetGroupMembers(FName GroupId, bool bIgnoreLeader);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    AEndCharacter* GetGroupIndividualMember(FName GroupId, FName IndividualTag);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    void GetExtraIntervalStatus(FName ID, float& ElapsedTime, bool& bActive, bool& bPause) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FEndAIDefinitionReturnTag GetCurrentAIDefinitionTagToChara(AEndCharacter* InChara) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FEndAIDefinitionReturnTag GetCurrentAIDefinitionTag() const;
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    void GetComboCount(int32& Count, int32& NextCount);
    
    UFUNCTION(BlueprintCallable)
    float GetBPPercent();
    
    UFUNCTION(BlueprintCallable)
    float GetBP();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAttackIntervalElapsedTime(EEndAIIntervalType IntervalType) const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAITimerRemainingTime(FName ID);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EActorMoveMode GetAIMoveMode();
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    EEndAIActionState GetAIActionState() const;
    
protected:
    UFUNCTION(BlueprintCallable)
    void ForceTakeDamegeHitReactionToParent(FName ReactionID);
    
    UFUNCTION(BlueprintCallable)
    void ForceEndCombination();
    
    UFUNCTION(BlueprintCallable)
    void EndGuardDefinition();
    
    UFUNCTION(BlueprintCallable)
    void EndBurstInstant();
    
    UFUNCTION(BlueprintCallable)
    void DisableLastHitAIPC(bool bDisable);
    
public:
    UFUNCTION(BlueprintCallable)
    void ClearTopPriorityActionConditionAll();
    
    UFUNCTION(BlueprintCallable)
    void ClearTopPriorityActionCondition(FName TopPriorityActionId);
    
    UFUNCTION(BlueprintCallable)
    void ClearHPMinLimit();
    
protected:
    UFUNCTION(BlueprintCallable)
    void ClearBPDamageCoefficient();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    void CheckAIActionStatus(TSubclassOf<UEndAIActionDefinition> ActionDefClass, bool& bResult, float& CoolTime, int32& TrialCount, int32& TrialStraightCount);
    
    UFUNCTION(BlueprintCallable)
    void ChangeCombinationTarget(AEndCharacter* InTarget);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void AsyncCheckConditionInvoke();
    
    UFUNCTION(BlueprintCallable)
    int32 AddDestructionPartsName(FName keyword, FName MeshName, FName destructionPartsLabelName, FName restorePartsLabelName);
    
};

