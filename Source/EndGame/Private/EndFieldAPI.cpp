#include "EndFieldAPI.h"

UEndFieldAPI::UEndFieldAPI() {
}

void UEndFieldAPI::WaitStable(const UObject* WorldContextObject, FLatentActionInfo LatentInfo) {
}

TArray<FName> UEndFieldAPI::StartReinforcementsWave(FName territoryID, EEndEnemyTerritoryWaveType Type, EEndEnemyTerritoryWavePopSettingOverwrite overwritePopSettings, int32 IntegerArgument00, int32 IntegerArgument01, int32 IntegerArgument02, int32 IntegerArgument03) {
    return TArray<FName>();
}

void UEndFieldAPI::ShowPreloadedWaveReinforcement(FName territoryID, FName reinforcementActorName, FTransform reinforcementStartPoint) {
}

void UEndFieldAPI::SetTruthLocationName(FName truthLocationName) {
}

void UEndFieldAPI::SetExecSlotIndex(int32 SlotIndex) {
}

void UEndFieldAPI::SetDebugFlag(EEndDebugFlag Flag) {
}

void UEndFieldAPI::SendStateTriggerDirect(const FString& StateTriggerName) {
}

void UEndFieldAPI::SendStateTriggerDelay(FName StateTriggerName) {
}

void UEndFieldAPI::SendStateTriggerByName(FName StateTriggerName) {
}

void UEndFieldAPI::SendStateTrigger(const FString& StateTriggerName) {
}

void UEndFieldAPI::SendPlannerEventTrigger(const FName& PlannerEventId, const FString& TriggerID) {
}

bool UEndFieldAPI::ResetFieldAiLookAtTarget(FName TargetActorName) {
    return false;
}

void UEndFieldAPI::RequestFinishUnusedWaveEnemiesFromTerritory(FName territoryID) {
}

void UEndFieldAPI::RequestDestroyEnemyInTerritory(FName territoryID, FName ActorName, bool setAsDead) {
}

void UEndFieldAPI::RefreshCacheBGM(const FString& cacheBGM) {
}

void UEndFieldAPI::PlayBGM(EndFieldBGMLayer Layer, FName BGM, float fadeStartTime, float fadeEndTime, bool CrossFade) {
}

bool UEndFieldAPI::IsWaveCharacter(AEndCharacter* Chara) {
    return false;
}

bool UEndFieldAPI::IsStable() {
    return false;
}

bool UEndFieldAPI::IsPreloadedWaveReinforcementLoaded(FName territoryID, FName reinforcementActorName) {
    return false;
}

bool UEndFieldAPI::IsEscaping() {
    return false;
}

bool UEndFieldAPI::IsEnableUpdateBattleParameter() {
    return false;
}

bool UEndFieldAPI::IsEnableSkipPauseMenu() {
    return false;
}

bool UEndFieldAPI::IsEnableFieldFullScreenMainMenu() {
    return false;
}

bool UEndFieldAPI::IsEnableFieldControler(bool bEncount) {
    return false;
}

bool UEndFieldAPI::IsDuringBattle() {
    return false;
}

bool UEndFieldAPI::IsCharacterInsideAnyBattleArea(const AActor* Character) {
    return false;
}

bool UEndFieldAPI::InvalidateTerritoryEncount(FName territoryID, bool Invalidate) {
    return false;
}

FName UEndFieldAPI::GetTerritoryIdFromActorName(FName ActorName) {
    return NAME_None;
}

FTransform UEndFieldAPI::GetEndTargetPointTransform(FName NodeName) {
    return FTransform{};
}

FVector UEndFieldAPI::GetEndTargetPointLocation(FName NodeName) {
    return FVector{};
}

int32 UEndFieldAPI::GetActionReportInteger(EEndActionReportType Type) {
    return 0;
}

FTransform UEndFieldAPI::FindEndTargetPoint(FName NodeName) {
    return FTransform{};
}

bool UEndFieldAPI::FieldAiLookAtTarget(FName TargetActorName, FName LookAtTargetActorName, FVector LookAtTargetLocation, float ReactionDistance, bool InIgnoreLookAtDeactiveAngle, bool InIsLookAwayFromActor) {
    return false;
}

void UEndFieldAPI::ExitLoation() {
}

void UEndFieldAPI::EntryLocation(const FName& LocationName) {
}

void UEndFieldAPI::ClearDebugFlag(EEndDebugFlag Flag) {
}

bool UEndFieldAPI::CheckExclusion(EndFieldExclusion enumValue) {
    return false;
}

void UEndFieldAPI::ChangeChapter(FName ChapterID, bool Debug, FName nextLocationRequestCurrentLocationId, bool selectChapter, EEndChapterQuestResetType questResetType, bool debugReserve) {
}

void UEndFieldAPI::CallbackCreatePlayerActor(const FName& partyActorName, AActor* Actor) {
}


