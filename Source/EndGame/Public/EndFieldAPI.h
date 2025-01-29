#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EEndChapterQuestResetType.h"
#include "EEndDebugFlag.h"
#include "Engine/LatentActionManager.h"
#include "EEndActionReportType.h"
#include "EEndEnemyTerritoryWavePopSettingOverwrite.h"
#include "EEndEnemyTerritoryWaveType.h"
#include "EndFieldBGMLayer.h"
#include "EndFieldExclusion.h"
#include "EndFieldAPI.generated.h"

class AActor;
class AEndCharacter;

UCLASS(Blueprintable, MinimalAPI)
class UEndFieldAPI : public UObject {
    GENERATED_BODY()
public:
    UEndFieldAPI();

    UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo", WorldContext="WorldContextObject"))
    static void WaitStable(const UObject* WorldContextObject, FLatentActionInfo LatentInfo);
    
    UFUNCTION(BlueprintCallable)
    static TArray<FName> StartReinforcementsWave(FName territoryID, EEndEnemyTerritoryWaveType Type, EEndEnemyTerritoryWavePopSettingOverwrite overwritePopSettings, int32 IntegerArgument00, int32 IntegerArgument01, int32 IntegerArgument02, int32 IntegerArgument03);
    
    UFUNCTION(BlueprintCallable)
    static void ShowPreloadedWaveReinforcement(FName territoryID, FName reinforcementActorName, FTransform reinforcementStartPoint);
    
    UFUNCTION(BlueprintCallable)
    static void SetTruthLocationName(FName truthLocationName);
    
    UFUNCTION(BlueprintCallable)
    static void SetExecSlotIndex(int32 SlotIndex);
    
    UFUNCTION(BlueprintCallable)
    static void SetDebugFlag(EEndDebugFlag Flag);
    
    UFUNCTION(BlueprintCallable)
    static void SendStateTriggerDirect(const FString& StateTriggerName);
    
    UFUNCTION(BlueprintCallable)
    static void SendStateTriggerDelay(FName StateTriggerName);
    
    UFUNCTION(BlueprintCallable)
    static void SendStateTriggerByName(FName StateTriggerName);
    
    UFUNCTION(BlueprintCallable)
    static void SendStateTrigger(const FString& StateTriggerName);
    
    UFUNCTION(BlueprintCallable)
    static void SendPlannerEventTrigger(const FName& PlannerEventId, const FString& TriggerID);
    
    UFUNCTION(BlueprintCallable)
    static bool ResetFieldAiLookAtTarget(FName TargetActorName);
    
    UFUNCTION(BlueprintCallable)
    static void RequestFinishUnusedWaveEnemiesFromTerritory(FName territoryID);
    
    UFUNCTION(BlueprintCallable)
    static void RequestDestroyEnemyInTerritory(FName territoryID, FName ActorName, bool setAsDead);
    
    UFUNCTION(BlueprintCallable)
    static void RefreshCacheBGM(const FString& cacheBGM);
    
    UFUNCTION(BlueprintCallable)
    static void PlayBGM(EndFieldBGMLayer Layer, FName BGM, float fadeStartTime, float fadeEndTime, bool CrossFade);
    
    UFUNCTION(BlueprintCallable)
    static bool IsWaveCharacter(AEndCharacter* Chara);
    
    UFUNCTION(BlueprintCallable)
    static bool IsStable();
    
    UFUNCTION(BlueprintCallable)
    static bool IsPreloadedWaveReinforcementLoaded(FName territoryID, FName reinforcementActorName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsEscaping();
    
    UFUNCTION(BlueprintCallable)
    static bool IsEnableUpdateBattleParameter();
    
    UFUNCTION(BlueprintCallable)
    static bool IsEnableSkipPauseMenu();
    
    UFUNCTION(BlueprintCallable)
    static bool IsEnableFieldFullScreenMainMenu();
    
    UFUNCTION(BlueprintCallable)
    static bool IsEnableFieldControler(bool bEncount);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsDuringBattle();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static bool IsCharacterInsideAnyBattleArea(const AActor* Character);
    
    UFUNCTION(BlueprintCallable)
    static bool InvalidateTerritoryEncount(FName territoryID, bool Invalidate);
    
    UFUNCTION(BlueprintCallable)
    static FName GetTerritoryIdFromActorName(FName ActorName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FTransform GetEndTargetPointTransform(FName NodeName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FVector GetEndTargetPointLocation(FName NodeName);
    
    UFUNCTION(BlueprintCallable)
    static int32 GetActionReportInteger(EEndActionReportType Type);
    
    UFUNCTION(BlueprintCallable)
    static FTransform FindEndTargetPoint(FName NodeName);
    
    UFUNCTION(BlueprintCallable)
    static bool FieldAiLookAtTarget(FName TargetActorName, FName LookAtTargetActorName, FVector LookAtTargetLocation, float ReactionDistance, bool InIgnoreLookAtDeactiveAngle, bool InIsLookAwayFromActor);
    
    UFUNCTION(BlueprintCallable)
    static void ExitLoation();
    
    UFUNCTION(BlueprintCallable)
    static void EntryLocation(const FName& LocationName);
    
    UFUNCTION(BlueprintCallable)
    static void ClearDebugFlag(EEndDebugFlag Flag);
    
    UFUNCTION(BlueprintCallable)
    static bool CheckExclusion(EndFieldExclusion enumValue);
    
    UFUNCTION(BlueprintCallable)
    static void ChangeChapter(FName ChapterID, bool Debug, FName nextLocationRequestCurrentLocationId, bool selectChapter, EEndChapterQuestResetType questResetType, bool debugReserve);
    
    UFUNCTION(BlueprintCallable)
    static void CallbackCreatePlayerActor(const FName& partyActorName, AActor* Actor);
    
};

