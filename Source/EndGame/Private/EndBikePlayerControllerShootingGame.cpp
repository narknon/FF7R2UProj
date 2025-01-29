#include "EndBikePlayerControllerShootingGame.h"

AEndBikePlayerControllerShootingGame::AEndBikePlayerControllerShootingGame(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MaxSpeed = 100.00f;
    this->Acceleration = 30.00f;
    this->ConstantArrivalTime = 1.00f;
    this->GuideAim = true;
    this->GuideAimMinDistance = 300.00f;
    this->GuideAimSpeed = 10.00f;
    this->CanShotWhileMoving = true;
    this->AttackCancelAnimDelay = 1.00f;
    this->CharacterBarret = NULL;
}

FVector AEndBikePlayerControllerShootingGame::GetAimLocation() const {
    return FVector{};
}


