#include "EndBikeAIHelicopterController.h"

AEndBikeAIHelicopterController::AEndBikeAIHelicopterController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InterpSpeedScaleOnPlayerBoostAccel = 10.00f;
    this->CanSendLogMissile = false;
}


