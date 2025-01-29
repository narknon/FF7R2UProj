#include "EndBattleLevelSequenceActor.h"

AEndBattleLevelSequenceActor::AEndBattleLevelSequenceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->CameraActor = NULL;
}

void AEndBattleLevelSequenceActor::OnStop() {
}

void AEndBattleLevelSequenceActor::OnFinished() {
}


