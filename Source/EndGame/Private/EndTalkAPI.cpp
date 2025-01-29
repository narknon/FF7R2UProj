#include "EndTalkAPI.h"

UEndTalkAPI::UEndTalkAPI() {
}

void UEndTalkAPI::StartPlannerEvent(const FName PlannerEventId) {
}

void UEndTalkAPI::StartBattleTalk(EndBattleTalkPriority Priority, const FName PlannerEventId, EndTalkRepeatType PlayType, float Interval_seconds, bool SkipOnBadStatus) {
}

void UEndTalkAPI::RequestBattleTalk(EndBattleTalkPriority Priority, const FName PlannerEventId, EndTalkRepeatType PlayType, float Interval_seconds, bool EndWithBattle, bool UseStack, bool UseStackWithouDuplicatedTalker, bool EndWithLocation, bool SkipPrevTalk, bool PreventSkipTalk, bool SkipOnBadStatus) {
}

void UEndTalkAPI::PlayBattleTalkStateByBP(FName TalkStateID, bool bForced, bool bEnableToStable) {
}

bool UEndTalkAPI::IsPlannerEventRunning(const FName PlannerEventId) {
    return false;
}

bool UEndTalkAPI::IsBattleTalkRunning(const FName PlannerEventId) {
    return false;
}

bool UEndTalkAPI::GetBattleTalkableRandomMemberName(FName& ActorName, const TArray<FName>& ignoreActorNameList) {
    return false;
}

bool UEndTalkAPI::ExportPVSaveData() {
    return false;
}

void UEndTalkAPI::EnableBattleTalkEventBox(FName TriggerBoxName) {
}

void UEndTalkAPI::DisableBattleTalkEventBox(FName TriggerBoxName) {
}


