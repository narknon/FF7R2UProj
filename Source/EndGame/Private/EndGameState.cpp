#include "EndGameState.h"

AEndGameState::AEndGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->GameState = EGameState::EGameState_NONE;
    this->GameStateChangeCount = 0;
    this->GameMode = EGameMode::EGameMode_PLAY_GAME;
    this->ActiveLocationSlot = 0;
    this->PrevActiveLocationSlot = 0;
    this->bRequestActiveLocation = false;
    this->bRequestTruthLocation = false;
    this->GameStatus = 0;
    this->GamePause = 0;
    this->RequestGamePauseOn = 0;
    this->RequestGamePauseOff = 0;
    this->NextPauseMenuKind = EEndSystemPauseMenuKind::None;
    this->HideWorld = false;
}

void AEndGameState::SetRequestGamePauseOn(EGamePause Pause) {
}

void AEndGameState::SetGameStatus(EGameStatus Status, bool Set) {
}

void AEndGameState::SendGameTrigger(const UObject* WorldContextObject, EGameTrigger Trigger, EGameState toState, FLatentActionInfo LatentInfo) {
}

void AEndGameState::OnDebugPauseFrameSkip() {
}

void AEndGameState::OnDebugPauseEnable() {
}

bool AEndGameState::IsGameStatus(EGameStatus Status) {
    return false;
}

bool AEndGameState::IsGamePause() {
    return false;
}

EGameState AEndGameState::GetGameState() const {
    return EGameState::EGameState_NONE;
}

float AEndGameState::GetGameSpeed() {
    return 0.0f;
}

void AEndGameState::ActivateLocation(FName TargetLocation) {
}


