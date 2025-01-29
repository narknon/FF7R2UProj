#include "EndBattleSceneBlueprint.h"

AEndBattleSceneBlueprint::AEndBattleSceneBlueprint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Phase = 1;
    this->bTickNewlySpawned = true;
}

void AEndBattleSceneBlueprint::SwitchCharaState(EEndBattleSceneCharaStateType& State, FName CharaName, bool bExecInState) {
}

void AEndBattleSceneBlueprint::SetPhase(int32 Value) {
}

void AEndBattleSceneBlueprint::SetCapturableBySummon(bool capturable) {
}

void AEndBattleSceneBlueprint::ResetSummonCondition() {
}

void AEndBattleSceneBlueprint::RequestAbilityToAI(AEndCharacter* Character, FName AbilityId, FLatentActionInfo LatentInfo) {
}































FName AEndBattleSceneBlueprint::GetTerritoryID() const {
    return NAME_None;
}

int32 AEndBattleSceneBlueprint::GetPhase() const {
    return 0;
}

TArray<AEndCharacter*> AEndBattleSceneBlueprint::GetEnemyAIGroupMembers(FName GroupId, bool bIgnoreLeader) {
    return TArray<AEndCharacter*>();
}

FName AEndBattleSceneBlueprint::GetBattleSceneBPName() const {
    return NAME_None;
}

void AEndBattleSceneBlueprint::ForceSuspendActionToEnemyAIAll() {
}

void AEndBattleSceneBlueprint::DoOnceWithThen(const EEndDoOnceCode Code, FLatentActionInfo LatentInfo, EEndDoOnceOutCode& Result) {
}

FName AEndBattleSceneBlueprint::ConvertMultiTalkPlayTriggerID(FName TalkPlayTriggerID) {
    return NAME_None;
}


void AEndBattleSceneBlueprint::BattleSceneDelay(float Duration, FLatentActionInfo LatentInfo) {
}

void AEndBattleSceneBlueprint::ApplyAIEnemyRightToAttack() {
}


