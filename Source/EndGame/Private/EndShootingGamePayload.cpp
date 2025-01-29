#include "EndShootingGamePayload.h"

FEndShootingGamePayload::FEndShootingGamePayload() {
    this->Priority = 0;
    this->Type = EEndShootingGameSectionType::CreateTarget;
    this->RouteIndex = 0;
    this->SpeedRate = 0.00f;
    this->bReverse = false;
    this->SurvivalTime = 0.00f;
    this->SEType = EShootingSEType::HitMastCloth;
    this->FFBEffestType = EShootingAdaptiveEffectType::Shot;
}

