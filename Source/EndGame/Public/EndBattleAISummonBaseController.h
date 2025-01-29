#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ESummonBattleBehavior.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndBattleSummonMinRangeLimitAbility.h"
#include "SummonChooseAbility.h"
#include "SummonComboAbility.h"
#include "SummonWarpPointMoveOnlyBattle.h"
#include "EndBattleAISummonBaseController.generated.h"

class AEndCharacter;

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleAISummonBaseController : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WarpMoveDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float UseWarpPointDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float CoolDownDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EscortDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SightAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxDistanceFromOwner;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSummonComboAbility ComboAbility;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSummonChooseAbility ChooseAbility;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MaxRangeAbility;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ReserveMaxRangeAbilitys;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FreeAngleAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBattleSummonMinRangeLimitAbility> MinRangeLimitAbilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSummonWarpPointMoveOnlyBattle> WarpPointMoveOnlyBattles;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetFoundNotAbilityChoice;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AbilityChoiceNotUsedInBattleBizarroSephiroth;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WarpMoveDistanceForBizarroSephiroth;
    
    AEndBattleAISummonBaseController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void WarpToCachedLocation();
    
    UFUNCTION(BlueprintCallable)
    void SetDrawPause(bool bDrawPause);
    
    UFUNCTION(BlueprintCallable)
    void SetAppear(bool bAppear);
    
    UFUNCTION(BlueprintCallable)
    bool RequestWarpTo(FVector WarpLocation);
    
    UFUNCTION(BlueprintCallable)
    void RequestShowCutSceneAbilityName();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnRequestUseAbility(FName AbilityId);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnPlayChangePhaseCutSceneFromBoss();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnInvokeCutSceneAbility(FName CutSceneID);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnEndBattle();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangeBattleBehavior(ESummonBattleBehavior NewBattleBehavior);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnBeginUltimateMagic();
    
    UFUNCTION(BlueprintCallable)
    void OnAppearNotify();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAppearEvent();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnAbilityChoice(FName choiceAbility);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsUsedMoogleAbility() const;
    
    UFUNCTION(BlueprintCallable)
    void CreateDamageSourceByCurrentTargetBase(FName DamageSourceID);
    
    UFUNCTION(BlueprintCallable)
    void ChangeMyTarget(AEndCharacter* InCharacter);
    
};

