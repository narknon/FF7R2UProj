#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EndBattleTalkPriority.h"
#include "EndTalkRepeatType.h"
#include "EndTalkAPI.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndTalkAPI : public UObject {
    GENERATED_BODY()
public:
    UEndTalkAPI();

    UFUNCTION(BlueprintCallable)
    static void StartPlannerEvent(const FName PlannerEventId);
    
    UFUNCTION(BlueprintCallable)
    static void StartBattleTalk(EndBattleTalkPriority Priority, const FName PlannerEventId, EndTalkRepeatType PlayType, float Interval_seconds, bool SkipOnBadStatus);
    
    UFUNCTION(BlueprintCallable)
    static void RequestBattleTalk(EndBattleTalkPriority Priority, const FName PlannerEventId, EndTalkRepeatType PlayType, float Interval_seconds, bool EndWithBattle, bool UseStack, bool UseStackWithouDuplicatedTalker, bool EndWithLocation, bool SkipPrevTalk, bool PreventSkipTalk, bool SkipOnBadStatus);
    
    UFUNCTION(BlueprintCallable)
    static void PlayBattleTalkStateByBP(FName TalkStateID, bool bForced, bool bEnableToStable);
    
    UFUNCTION(BlueprintCallable)
    static bool IsPlannerEventRunning(const FName PlannerEventId);
    
    UFUNCTION(BlueprintCallable)
    static bool IsBattleTalkRunning(const FName PlannerEventId);
    
    UFUNCTION(BlueprintCallable)
    static bool GetBattleTalkableRandomMemberName(FName& ActorName, const TArray<FName>& ignoreActorNameList);
    
    UFUNCTION(BlueprintCallable)
    static bool ExportPVSaveData();
    
    UFUNCTION(BlueprintCallable)
    static void EnableBattleTalkEventBox(FName TriggerBoxName);
    
    UFUNCTION(BlueprintCallable)
    static void DisableBattleTalkEventBox(FName TriggerBoxName);
    
};

