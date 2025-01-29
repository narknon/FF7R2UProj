#pragma once
#include "CoreMinimal.h"
#include "EPlayerType.h"
#include "EAIPCBattleParamType.h"
#include "EEndAiMoveType.h"
#include "EFriendAbilityTargetType.h"
#include "EFriendBattleCautionType.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndBattleAITargetChoosingParam.h"
#include "EndBattleFriendAbilityParam.h"
#include "EndBattleFriendSpecialAbilityParam.h"
#include "Templates/SubclassOf.h"
#include "EndAIControllerFriendBase.generated.h"

class AEndCharacter;
class UEndAIBattleParamBase;

UCLASS(Blueprintable, MinimalAPI)
class AEndAIControllerFriendBase : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBattleAITargetChoosingParam TargetChoosingParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GroundTargetReachableHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AirTargetReachableHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bDoRangedAttack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanStrafeMove;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanGuard;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> NotifyPartyStatusChangeId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EPlayerType> NotifyPartyPriorityList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EFriendBattleCautionType BattleCautionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMoveType BattleCautionMoveType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BattleCautionLeaderDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BattleCautionFriendDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NormalAttackAbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 HardAttackFrequency;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBattleFriendAbilityParam> HardAttackParams;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBattleFriendSpecialAbilityParam> SpecialAttackParams;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EAIPCBattleParamType, TSubclassOf<UEndAIBattleParamBase>> BattleParams;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIBattleParamBase> ToadBattleParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StandbyTimeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StandbyTimeMin;
    
public:
    AEndAIControllerFriendBase(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable)
    bool RequestAbility(FName AbilityId, EFriendAbilityTargetType TargetType, bool bPriority, AEndCharacter* Target, FName prevComboAbilityId, bool bRetryFailed);
    
    UFUNCTION(BlueprintCallable)
    void OverrideCooldownTimer(float Time, bool bForce);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartRequestedAbilityInvoke(FName AbilityId);
    
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlayerPartyStatusChange(AEndCharacter* Target, const TArray<FName>& idList);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlayerPartyEmergency(AEndCharacter* Target);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAbilityInterruptInvoke(FName AbilityId);
    
};

