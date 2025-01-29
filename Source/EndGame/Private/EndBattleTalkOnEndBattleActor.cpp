#include "EndBattleTalkOnEndBattleActor.h"

AEndBattleTalkOnEndBattleActor::AEndBattleTalkOnEndBattleActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DelayMinSeconds = 0.00f;
    this->DelayMaxSeconds = 0.00f;
}

void AEndBattleTalkOnEndBattleActor::PlayVoice(bool bUnuseDefaultDelay, float OverrideDelayMinSeconds, float OverrideDelayMaxSeconds, FName VoiceSetId) {
}



