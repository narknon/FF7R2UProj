#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinitionFastDashEventTiming.h"
#include "EEndAiMoveType.h"
#include "EEndBattleAbilityActionCategory.h"
#include "EEndBattleEnemyCombinationAbilityFinishResult.h"
#include "EndAIBattlePhaseInfo.h"
#include "EndAIControllerEnemyBase.h"
#include "EndBattleReplaceCombinationCounterExecuteAbilityIDParam.h"
#include "Templates/SubclassOf.h"
#include "EndAIControllerBossBase.generated.h"

class AEndCharacter;
class UEndAIActionDefinitionBase;
class UEndAIMoveDefinition;

UCLASS(Blueprintable)
class AEndAIControllerBossBase : public AEndAIControllerEnemyBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAIBattlePhaseInfo> m_BattlePhaseInfos;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_PhaseNumberLocationWorkName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_PhaseChangeGroupId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName m_PhaseChangeGroupIndividualTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bPhaseChangeShareBase;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool m_bPhaseChangeAnyOneReaction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseOverrideAbilityTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideAbilityTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseOverrideDamageTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideDamageTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseOverrideActionRestrictionTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideActionRestrictionTimeRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndBattleReplaceCombinationCounterExecuteAbilityIDParam> ReplaceCombinationCounterExecuteAbilityIDMap;
    
    AEndAIControllerBossBase(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable)
    void SwitchWallMove_EN0007();
    
    UFUNCTION(BlueprintCallable)
    void StopEnvironmentFeelerTornade(FName LevelName, FName AccessID, bool bDetach, bool bUseFade, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void StopEnvironmentFeelerLaser(FName LevelName, FName AccessID, bool bDetach, bool bUseFade, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void StopEnvironmentFeeler(FName LevelName, FName AccessID, bool bUseFade, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void SetDebugChangePhase(int32 Phase);
    
    UFUNCTION(BlueprintCallable)
    void RestoreStalactite_EB2000();
    
    UFUNCTION(BlueprintCallable)
    bool RequestPhaseChangeAbility(FName AbilityId);
    
    UFUNCTION(BlueprintCallable)
    void RequestManualPhaseChange(float Delay, bool CanPhaseChangeToDisableReaction);
    
    UFUNCTION(BlueprintCallable)
    void RemoveWallMoveSettings_EN0007();
    
    UFUNCTION(BlueprintCallable)
    void PlayEnvironmentFeelerTornade(FName LevelName, FName AccessID, FName DamageSourceID, bool bUseFade, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void PlayEnvironmentFeelerLaser(FName LevelName, FName AccessID, FName AttachName, bool bUseFade, float BlendTime);
    
    UFUNCTION(BlueprintCallable)
    void PlayEnvironmentFeeler(FName LevelName, FName AccessID, bool bUseFade, float BlendTime);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnWarpFromCliffInvoke_EB2020();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnWallMoveToWallInvoke_EN0007();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnWallMoveToGroundInvoke_EN0007();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeDamagePhaseChangeHpLineInvoke(int32 Phase);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartWallPhaseInvoke_EB2000();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartCeilingPhaseInvoke_EB2000();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnFastDashTimingInvoke_EB2160(EEndAIMoveDefinitionFastDashEventTiming Timing, int32 Index, FName MoveDefTag);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnFastDashArrivalInvoke_EB0016(FName Tag, bool bSuccessAction);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEnemyCombinationFinishInvoke(EEndBattleEnemyCombinationAbilityFinishResult FinishedResult, int32 FinishedOnAbility);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangePhaseReadyInvoke(int32 PrevPhase, int32 NextPhase);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangePhaseReactionAfterInvoke(int32 NextPhase, FName HitReactionID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangePhaseFinishInvoke(int32 PrevPhase, int32 NextPhase);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginFallFromCliffInvoke_EB2020();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBattleEventInvoke(FName EventName);
    
    UFUNCTION(BlueprintCallable)
    void NotifyAbilitySuccessToTargetSystem(AEndCharacter* Target, EEndBattleAbilityActionCategory ActionCategory);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsChangingPhase();
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetTotalStalactiteNum_EB2000();
    
    UFUNCTION(BlueprintCallable)
    void ForceStopEnemyCombinationAbility();
    
    UFUNCTION(BlueprintCallable)
    bool ForceRequestAction(TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass, TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass);
    
    UFUNCTION(BlueprintCallable)
    void FallStalactite_EB2000();
    
    UFUNCTION(BlueprintCallable)
    void ChangeWallMoveType_EN0007(EEndAiMoveType MoveType);
    
};

