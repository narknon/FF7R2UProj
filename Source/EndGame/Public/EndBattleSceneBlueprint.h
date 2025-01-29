#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndBattleAttributeType.h"
#include "EEndBattleCountLogType.h"
#include "EEndBattleSpecialStatusChangeType.h"
#include "EEndBattleSyncActionStateType.h"
#include "EndDataObjectBattleDamageSourceAccessor.h"
#include "GameFramework/Actor.h"
#include "Engine/LatentActionManager.h"
#include "EEndBattleSceneCharaStateType.h"
#include "EEndBattleTalkInterruptReason.h"
#include "EEndDoOnceCode.h"
#include "EEndDoOnceOutCode.h"
#include "EndAIEnemyRightToAttackInfo.h"
#include "EndBattleSceneBlueprint.generated.h"

class AEndCharacter;

UCLASS(Blueprintable)
class AEndBattleSceneBlueprint : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Phase;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bTickNewlySpawned;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIEnemyRightToAttackInfo AIEnemyRightToAttackInfo;
    
public:
    AEndBattleSceneBlueprint(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SwitchCharaState(EEndBattleSceneCharaStateType& State, FName CharaName, bool bExecInState);
    
    UFUNCTION(BlueprintCallable)
    void SetPhase(int32 Value);
    
    UFUNCTION(BlueprintCallable)
    void SetCapturableBySummon(bool capturable);
    
    UFUNCTION(BlueprintCallable)
    void ResetSummonCondition();
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"))
    void RequestAbilityToAI(AEndCharacter* Character, FName AbilityId, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnTakeDamage(int32 Damage, const FName& CauserCharaName, const FName& DamagedCharaName, const FName& AbilityId, bool bBind, bool bGuard, const FName& hitBoneName, bool bAttributeHit, bool bResistHit, const FName& DamageSourceID, EEndBattleAttributeType appendAttribute, float justHitRotYaw, const FVector& hitPosition, bool bHeal, bool bBurst, bool bLock);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartBattleJenovaLife();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnRemoveStatusChangeID(const FName CharaName, const TArray<FName>& IDs);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnReadyBattleTalk(FName territoryID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPostEntryBattleScene();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMotionMessage(FName CharaName, FName MotionName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnMetaMessage(const FString& InMessage);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnIncrementBattleCountPerID(FName CauserCharaName, FName TargetCharaName, EEndBattleCountLogType Type, FName ID, int32 Count);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnExitDummyBattleScene();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnExitBattleScene();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEntryDummyBattleScene(const FName& battleScenenBPName, const FName& territoryID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEntryBattleScene(const FName& battleScenenBPName, const FName& territoryID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndTalkTriggerBoxCollide(FName TriggerBoxActorName, FName CollideCharaName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndRailCamera(const FName& RailCameraID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndCutScene(const FName& CutSceneID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndCombinationAbility(const FName& CombinationAbilityId, bool hitDamageSource, FName useCharacterName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnDLCSummonUltimateMagicEnd();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCutSceneMessageInvoke(const FName& Message);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCollideBattleTalkColideBox(FName ColideBoxName, AEndCharacter* OwnerChara, FName DamageSourceID, FEndDataObjectBattleDamageSourceAccessor DamageSourceDataObject);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCharaSyncAction(const FName& AttackedCharaName, const FName& ReceivedCharaName, EEndBattleSyncActionStateType StateType, int32 StateCount, const FName& SyncActionID, const FName& CauserCharaName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCharaSpecialStatusChange(const FName& ownerCharaName, const FName& SpecialStatusChangeID, EEndBattleSpecialStatusChangeType Type, const FName& StateId, const TArray<float>& Params, const TArray<FName>& ParamIDs, const TArray<AActor*>& ParamActors);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCharaPartsDamage(FName CauserCharaName, FName DamagedCharaName, FName PartsID, FName CategoryID, int32 RemainHP, float RemainHPPer);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnCharaPartsBreak(FName CauserCharaName, FName BrokenCharaName, FName PartsID, FName CategoryID, int32 CategoryBreakCount);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBPMessageFromAIBP(AEndCharacter* SendCharacter, const FName& Message);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginTalkTriggerBoxCollide(FName TriggerBoxActorName, FName CollideCharaName);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginCutScene(const FName& CutSceneID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginCombinationAbility(const FName& CombinationAbilityId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBattleTalkInterrupted(FName TalkID, EEndBattleTalkInterruptReason SkipReason);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBattleTalkEnded(FName TalkID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAddStatusChangeID(const FName CharaName, const TArray<FName>& IDs);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetTerritoryID() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetPhase() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<AEndCharacter*> GetEnemyAIGroupMembers(FName GroupId, bool bIgnoreLeader);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetBattleSceneBPName() const;
    
    UFUNCTION(BlueprintCallable)
    void ForceSuspendActionToEnemyAIAll();
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"))
    void DoOnceWithThen(const EEndDoOnceCode Code, FLatentActionInfo LatentInfo, EEndDoOnceOutCode& Result);
    
    UFUNCTION(BlueprintCallable)
    FName ConvertMultiTalkPlayTriggerID(FName TalkPlayTriggerID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ChangePhase(int32 _phase);
    
    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"))
    void BattleSceneDelay(float Duration, FLatentActionInfo LatentInfo);
    
protected:
    UFUNCTION(BlueprintCallable)
    void ApplyAIEnemyRightToAttack();
    
};

