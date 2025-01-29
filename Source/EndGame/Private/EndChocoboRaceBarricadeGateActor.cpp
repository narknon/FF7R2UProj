#include "EndChocoboRaceBarricadeGateActor.h"

AEndChocoboRaceBarricadeGateActor::AEndChocoboRaceBarricadeGateActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->GateClass = NULL;
    this->bOpenStart = false;
    this->OpenTime = 4.00f;
    this->CloseTime = 4.00f;
}


