#include "EndGameMode.h"

AEndGameMode::AEndGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DebugGameMode = false;
    this->DebugGameMode_Normal = false;
    this->DebugGameModeFlags = 0;
    this->GamePlayMode = false;
    this->TotalTickTime = 0;
    this->FrameTickTime = 0;
    this->FrameTickCount = 0;
    this->SystemDeltaTimeSeconds = 0.00f;
    this->CrossSaveManager = NULL;
    this->EndOneSaveDataManager = NULL;
    this->SequenceAppContentWidget = NULL;
    this->GameJumpActor = NULL;
    this->PartyCoordinator = NULL;
}

void AEndGameMode::InitEditorPreviewGameMode(const UObject* WorldContextObject, FLatentActionInfo LatentInfo) {
}

void AEndGameMode::InitEditorGameMode(const UObject* WorldContextObject, FName LocationName, bool QuickStart, FName InCutName, FLatentActionInfo LatentInfo) {
}

void AEndGameMode::InitBootSequence() {
}


